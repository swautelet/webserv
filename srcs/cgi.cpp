#include "cgi.hpp"

#define BUFF_SIZE 1000
std::string	Cgi::start_script(webServ& web)
{
	std::string rep;
	int id;
//	std::FILE *infile = tmpfile();
//	std::FILE *outfile = tmpfile();
	int status;
	(void)status;
	int outpip[2];
	char** argtmp = getArgv();
	char** envtmp = getEnvp();
	char *exec_path;
	(void)exec_path;
	
	pipe(outpip);
	char buffer[10];
	int ret;
	std::cout << "This :" << web.getCgi().getPath() << " received this brutbody::::::::::::::::::::::::::::::::::::::::::::::::::"<< std::endl;
	while ((ret = read(web.getReq().getBrutbody_fileno(), buffer, 10)) > 0)
	{
		write(1, buffer, ret);
	}
	std::cout << "finish ---------------------------------------" << std::endl;
	lseek(web.getReq().getBrutbody_fileno(), 0, SEEK_SET);
	id = fork();
	if (id == -1)
	{
		std::cout << "could'nt fork" << std::endl;
		return rep;
	}
	if (id == 0)
	{
		close (outpip[0]);
		// std::cout << "starting execve with : " << getPath() << std::endl;
		// print_tab(argtmp);
		// print_tab(envtmp);
		dup2(outpip[1], STDOUT_FILENO);
		dup2(web.getReq().getBrutbody_fileno(), STDIN_FILENO);
		char* temp = to_char(getPath());
		
		if (execve(temp, argtmp, envtmp) < 0)
		{
			delete[] temp;
			std::cout << "Script couldn't be loaded with this->script : |" << argtmp[1] << "|" << std::endl;
			std::cout << "and this->exe :" << getPath() << std::endl;
			// std::cout << "errno : " << errno << std::endl;
			perror("EXECVE ERROR :");
			exit(10);
		}
	}
	else
	{
		// std::cout << "waiting for script" << std::endl;
		// waitpid(id, &status, 0);
		close(outpip[1]);
		//  std::cout << "php script finished with :" << status << std::endl;
		char buff[BUFF_SIZE + 1];
		buff[BUFF_SIZE] = '\0';
		int size;
		while((size = read(outpip[0], buff, BUFF_SIZE)) > 0)
		{
			for (int i = size; i <= BUFF_SIZE; i++)
				buff[i] = '\0';
			rep += buff;
		}
		std::cout << "buff " << buff << std::endl;
		// std::cout << "waiting for php " << std::endl;
		// wait(&status);
	}
	// std::cout << "php script answered with ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << std::endl << rep << std::endl << "-------------------------------------------------------------------------------------------" << std::endl;
	close(outpip[0]);
//	fclose(infile);
//	fclose(outfile);
	// free_table(argtmp);
	// free_table(envtmp);
	delete[] argtmp;
	delete[] envtmp;
	return rep;
}

void Cgi::run_api(webServ& web, confData& conf)
{
	web.getCgi().setFullpath(web, conf);
	web.getCgi().setEnv(web, conf);
	body = web.getReq().getBody();
	// std::cout << "----------------------debug env------------------" << std::endl;
	// for (unsigned long i = 0; i < env.size(); i++)
	// {
	// 	std::cout << "|" << env[i] << "|" << std::endl;
	// }
	// std::cout << "--------------------------------------- finish --------------------------------" << std::endl;
	web.getRes().setBody(web.getCgi().start_script(web));
	web.getRes().setContentType();
	web.getRes().setStatus(200);
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
	find_transla_path("php-cgi", "php", paths);
	find_transla_path("python3", "py", paths);
}

void	Cgi::find_transla_path(std::string scri, std::string ext, std::vector<std::string> paths)
{
	for (unsigned long i = 0; i < paths.size(); i++)
	{
		std::string tmp = paths[i] + "/" + scri;
		char* temp = to_char(tmp);
		if (!access(temp, X_OK))
		{
			delete[] temp;
			pathmap[ext] = tmp;
			std::cout << "i initialized script :" << ext << " with :" << tmp << std::endl;
			break ;
		}
		delete[] temp;
	}
}

char**	Cgi::getArgv()
{
	char **res = new char*[3];
	res[0] = new char[this->getPath().size() + 1];
	res[1] = new char[this->scripath.size() + 1];
	res[2] = NULL;
	std::string name = this->getPath();
	for (unsigned long i = 0; i < name.size(); i++)
	{
		res[0][i] = name[i];
	}
	res[0][name.size()] = '\0';
	for (unsigned long i = 0; i < this->scripath.size(); i++)
	{
		res[1][i] = this->scripath[i];
	}
	res[1][this->scripath.size()] = '\0';
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
	if (temp.rfind('?') != std::string::npos)
	{
		temp = temp.substr(0, temp.rfind('?'));
	}
	std::string locname = location_exe(conf, temp);
	std::string locroot;
	if (!locname.empty())
	{
		locroot = conf.getGoodLocation(locname).getPath();
	}
	else
	{
		locroot = conf.getPath();
	}
	if (locroot.size() > 0 && locroot[0] == '.')
		locroot = locroot.substr(1, locroot.size());
	this->scripath = web.getServ_Root() + locroot + temp;
}

void	Cgi::setEnv(webServ& web, confData& conf)
{
	(void)conf;
	std::vector<std::string> header;
	splitstring(web.getReq().getHeader(), header, '\n');

	env.clear();
//	std::cout << "body req is :" << std::endl << web.getReq().getBody() << std::endl;
	std::string tmp = "REDIRECT_STATUS=200";
	env.push_back(tmp);
	tmp = "GATEWAY_INTERFACE=CGI/1.1";
	env.push_back(tmp);
	// tmp = "SCRIPT_NAME=" + this->scripath.substr(this->scripath.rfind('/') + 1, this->scripath.size());
	// env.push_back(tmp);
	tmp = "SCRIPT_FILENAME=" + this->scripath;
	env.push_back(tmp);
	tmp = "REQUEST_METHOD=" + web.getReq().getMethod();
	env.push_back(tmp);
	if (web.getReq().getContentLength().compare("0"))
	{
		tmp = "CONTENT_LENGTH="+ web.getReq().getContentLength();
		if (!tmp.empty() && !isalnum(tmp.back())) {
   	     tmp.resize(tmp.size() - 1);
   		}
		env.push_back(tmp);
	}
	//  + itoa(web.getReq().getQuery_string().size());
	tmp = search_value_vect(header, "Content-Type:");
	if (tmp.size())
	{
		// if (tmp.find(';') != std::string::npos)
		// 	tmp = tmp.substr(0, tmp.find(';'));
		tmp = "CONTENT_TYPE=" + tmp;
		env.push_back(tmp);
	}
	tmp = "PATH_INFO=" + web.getReq().getUrl();
	env.push_back(tmp);
	tmp = "PATH_TRANSLATED=" + web.getReq().getUrl();
	env.push_back(tmp);
	if (!web.getReq().getQuery_string().empty())
	{
		std::cout << "GET" << std::endl;
		tmp = "QUERY_STRING=" + web.getReq().getQuery_string();
		env.push_back(tmp);
	}
	// else
	// {
		// tmp = "QUERY_STRING=" + web.getReq().getBody();
		// env.push_back(tmp);
	// }
	tmp = "REMOTEaddr=" + conf.getAdress();
	env.push_back(tmp);
	// tmp = "REMOTE_IDENT=" + search_value_vect(header, "Authorization:");
	// env.push_back(tmp);
	// tmp = "REMOTE_USER=" + search_value_vect(header, "Authorization:");
	// env.push_back(tmp);
	tmp = "REQUEST_URI=" + web.getReq().getUrl();
	if (!web.getReq().getQuery_string().empty())
		tmp += "?" + web.getReq().getQuery_string();
	env.push_back(tmp);
	tmp = "SERVER_NAME=";
	if(search_value_vect(header, "Host:").size())
	{
		tmp += search_value_vect(header, "Host:");
	}
	else
	{
		tmp += conf.getServName();
	}
	if (!tmp.empty() && !isalnum(tmp.back())) {
        tmp.resize(tmp.size() - 1);
    }
	//  + itoa(web.getReq().getQuery_string().size());
	env.push_back(tmp);
	tmp = "PATH_INFO=" + web.getReq().getUrl();
	env.push_back(tmp);
	// tmp = "PATH_TRANSLATED=" + web.getReq().getUrl();
	// env.push_back(tmp);
	// tmp = "REMOTEaddr=" + conf.getAdress();
	// env.push_back(tmp);
	// tmp = "REMOTE_IDENT=" + search_value_vect(header, "Authorization:");
	// env.push_back(tmp);
	// tmp = "REMOTE_USER=" + search_value_vect(header, "Authorization:");
	// env.push_back(tmp);
	// tmp = "REQUEST_URI=" + web.getReq().getUrl();
	// if (!web.getReq().getQuery_string().empty())
	// 	tmp += "?" + web.getReq().getQuery_string();
	// env.push_back(tmp);
	// tmp = "SERVER_NAME=";
	// if(search_value_vect(header, "Host: ").size())
	// {
	// 	tmp += search_value_vect(header, "Host: ");
	// }
	// else
	// {
	// 	tmp += conf.getServName();
	// }
	// if (!tmp.empty() && !isalnum(tmp.back())) {
    //     tmp.resize(tmp.size() - 1);
    // }
	//env.push_back(tmp);
	// tmp = "SERVER_PORT=" + conf.getPort();
	// env.push_back(tmp);
	tmp = "SERVER_PROTOCOL=HTTP/1.1";
	env.push_back(tmp);
	tmp = "SERVER_SOFTWARE=Webserv/1.0";
	env.push_back(tmp);
	tmp = "PHPRC=" + web.getServ_Root() + "/www/php/include/php.ini";
	env.push_back(tmp);
	// tmp = "HTTP_=" + web.getReq().getHeader();
	// env.push_back(tmp);
	for (unsigned long i = 0; i < env.size(); i++)
	{
		for (unsigned long j = 0; j < env[i].size(); j++)
		{
			if (env[i][j] == '\r')
				std::cout << "WARNING FANTOM CHAR STILL SOMEWHERE " << "OIUFHIEUFHWOIFOEWIFJOIEWJOFIEW" << std::endl;
		}
	}
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
