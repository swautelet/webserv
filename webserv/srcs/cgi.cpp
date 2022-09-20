#include "cgi.hpp"
#define BUFF_SIZE 50

std::string	Cgi::start_script()
{
	std::string rep;
	int id;
	std::FILE *infile = tmpfile();
	std::FILE *outfile = tmpfile();
	int status;
	// int pip[2];
	char** argtmp = getArgv();
	char** envtmp = getEnvp();
/*	std::cout << "compared with real table ---------------------------" << std::endl;
	for (int i = 0; envtmp[i]; i++)
	{
		std::cout << envtmp[i] << std::endl;
	}*/
	std::string test = "ceci est un test ";
	write(fileno(infile),test.c_str(), test.size());
	lseek(fileno(infile), 0, SEEK_SET);
	// pipe(pip);
	id = fork();
	if (id == -1)
	{
		std::cout << "could'nt fork" << std::endl;
		return rep;
	}
	if (id == 0)
	{
		// close (pip[0]);
		dup2(fileno(outfile), STDOUT_FILENO);
		dup2(fileno(infile), STDIN_FILENO);
		// std::cout << "Hello from php script process" << std::endl;
		std::string tmp = getPath() + " " + scripath;
		std::system(tmp.c_str());
		exit (10);
		/*if (execve(getPath().c_str(), argtmp, envtmp) < 0)
		{
			std::cout << "Script couldn't be loaded with this->scripath : |" << getFullpath() << "|" << std::endl;
			std::cout << "ex this->scripath :" << getPath() << std::endl;
			std::cout << "errno : " << errno << std::endl;
			perror("execve error ");
			exit(10);
		}*/
	}
	else
	{
		// close(pip[1]);
		waitpid(id, &status, 0);
		// std::cout << "php script finished with :" << status << std::endl;
		lseek(fileno(outfile), 0, SEEK_SET);
		char buff[11];
		buff[10] = '\0';
		int size;
		std::cout << "i read that :" << std::endl;
		while((size = read(fileno(outfile), buff, 10)) > 0)
		{
			write(1, buff, size);
			for (int i = size; i < 10; i++)
				buff[i] = '\0';
			rep += buff;
		}
		// std::cout << "waiting for php " << std::endl;
		// wait(&status);
	}
	fclose(infile);
	fclose(outfile);
	free_table(argtmp);
	free_table(envtmp);
	return rep;
}

void Cgi::run_api(webServ& web, confData& conf)
{
	web.getCgi().setFullpath(web, conf);
	web.getCgi().setEnv(web, conf);
	std::cout << "----------------------debug env------------------" << std::endl;
	for (unsigned long i = 0; i < env.size(); i++)
	{
		std::cout << env[i] << std::endl;
	}
	web.getRes().setBody(web.getCgi().start_script());
	web.getRes().setContentType();
}

Cgi::Cgi()
{
	// infile = tmpfile();
//	this->this->scripath = new std::vector<std::string>;
}

Cgi::~Cgi()
{
	// fclose(infile);
//	delete this->scripath;
}

std::string& Cgi::getPath()
{
	std::string ext = this->scripath.substr(this->scripath.rfind('.') + 1, this->scripath.size());
	return pathmap[ext];
}

void	Cgi::set_transla_path(char** envp)
{
	std::vector<std::string> paths;
	std::string searched = "PATH=";
	for (int i = 0; envp[i]; i++)
	{
		std::string tmp(envp[i]);
		if (!tmp.substr(0, searched.size()).compare(searched))
		{
			splitstring(tmp.substr(5, tmp.size()), paths, ':');
			break;
		}
	}
	find_transla_path("php", paths);
}

void	Cgi::find_transla_path(std::string scri, std::vector<std::string> paths)
{
	for (unsigned long i = 0; i < paths.size(); i++)
	{
		std::string tmp = paths[i] + "/" + scri;
		if (!access(tmp.c_str(), X_OK))
		{
			pathmap[scri] = tmp;
			break ;
		}
	}
}

char**	Cgi::getArgv()
{
	char **res = new char*[2];
	res[0] = new char[this->scripath.size() + 1];
	res[1] = NULL;
	for (unsigned long i = 0; i < this->scripath.size(); i++)
	{
		res[0][i] = this->scripath[i];
	}
	res[0][this->scripath.size()] = '\0';
	return res;
}

const std::vector<std::string>& Cgi::getEnv() const
{
	return env;
}

const std::string& Cgi::getFullpath() const
{
	return this->scripath;
}

void	Cgi::setFullpath(webServ& web,confData& conf)
{
	std::string temp (web.getReq().getUrl());
	location loc = conf.LocationFinder(temp);
	std::string locroot (loc.getPath());
	if (locroot.size() >= 1 && locroot[0] == '.')
		locroot = locroot.substr(1, locroot.size());
	temp = temp.substr(loc.getLocation_name().size(), temp.size());
	this->scripath = web.getServ_Root() + locroot + "/" + temp;
}

void	Cgi::setEnv(webServ& web, confData& conf)
{
	std::vector<std::string> header;
	splitstring(web.getReq().getBody(), header, '\n');

	env.clear();
//	std::cout << "body req is :" << std::endl << web.getReq().getBody() << std::endl;
	std::string tmp = "REDIRECT_STATUS=200";
	env.push_back(tmp);
	tmp = "GATEWAY_INTERFACE=CGI/1.1";
	env.push_back(tmp);
	tmp = "SCRIPT_NAME=" + this->scripath.substr(this->scripath.rfind('/') + 1, this->scripath.size());
	env.push_back(tmp);
	tmp = "SCRIPT_FILENAME=" + this->scripath;
	env.push_back(tmp);
	tmp = "REQUEST_METHOD=" + web.getReq().getMethod();
	env.push_back(tmp);
	tmp = "CONTENT_LENGTH=" + itoa(web.getReq().getHeader().size());
	env.push_back(tmp);
	tmp = "CONTENT_TYPE=" + search_value_vect(header, "Accept:");
	env.push_back(tmp);
	tmp = "PATH_INFO=" + web.getReq().getUrl();
	env.push_back(tmp);
	tmp = "PATH_TRANSLATED=" + web.getReq().getUrl();
	env.push_back(tmp);
	tmp = "QUERY_STRING=" + web.getReq().getUrl().substr(web.getReq().getUrl().rfind('?') + 1, web.getReq().getUrl().size());
	env.push_back(tmp);
	tmp = "REMOTEaddr=" + conf.getAdress();
	env.push_back(tmp);
	tmp = "REMOTE_IDENT=" + search_value_vect(header, "Authorization: ");
	env.push_back(tmp);
	tmp = "REMOTE_USER=" + search_value_vect(header, "Authorization: ");
	env.push_back(tmp);
	tmp = "REQUEST_URI=" + web.getReq().getUrl();
	env.push_back(tmp);
	tmp = "SERVER_NAME=";
	if(search_value_vect(header, "Host: ").size())
	{
		tmp += search_value_vect(header, "Host: ");
	}
	else
	{
		tmp += conf.getServName();
	}
	env.push_back(tmp);
	tmp = "SERVER_PORT=" + conf.getPort();
	env.push_back(tmp);
	tmp = "SERVER_PROTOCOL=HTTP/1.1";
	env.push_back(tmp);
	tmp = "SERVER_SOFTWARE=Webserv/1.0";
	env.push_back(tmp);
}

char**	Cgi::getEnvp()
{
	char** res = new char*[env.size() + 1];
	res[env.size()] = NULL;
	for (unsigned long i = 0; i < env.size(); i++)
	{
		res[i] = new char[env[i].size() + 1];
		res[i][env[i].size()] = '\0';
		for (unsigned long j = 0; j <env[i].size(); j++)
		{
			res[i][j] = env[i][j];
		}
	}
	return res;
}
