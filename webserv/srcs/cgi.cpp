#include "cgi.hpp"
#define BUFF_SIZE 50

void	Cgi::start_script()
{
	int id;
	int status;
	char** argtmp = vectstring_tochartable(fullpath);
	char** envtmp = vectstring_tochartable(env);
	id = fork();
	if (id == -1)
	{
		std::cout << "could'nt fork" << std::endl;
		return ;
	}
	if (id == 0)
	{
		if (execve(getPath(fullpath[0]).c_str(), argtmp, envtmp) < 0)
		{
			std::cout << "Script couldn't be loaded with path : |" << fullpath[0] << "|" << std::endl;
			std::cout << "ex path :" << getPath(fullpath[0]) << std::endl;
			std::cout << "errno : " << errno << std::endl;
			perror("execve error ");
			exit(0);
		}
	}
	else
	{
		wait(&status);
	}
	free_table(argtmp);
	free_table(envtmp);
}

void run_api(webServ& web, confData& conf)
{
	web.getCgi().setFullpath(web, conf);
	web.getCgi().setEnv(web, conf);
	web.getCgi().start_script();
}

Cgi::Cgi():fullpath(1)
{
	pathmap["php"] = "/opt/homebrew/bin/php";
}

Cgi::~Cgi()
{
}

std::string& Cgi::getPath(std::string& req_file)
{
	std::string ext(req_file.substr(req_file.rfind('.') + 1, req_file.size()));
	return pathmap[ext];
}

const std::vector<std::string>& Cgi::getEnv() const
{
	return env;
}

const std::vector<std::string>& Cgi::getArg() const
{
	return arg;
}

const std::string& Cgi::getFullpath() const
{
	return fullpath[0];
}

void	Cgi::setFullpath(webServ& web,confData& conf)
{
	std::string path (web.getReq().getUrl());
	location loc = conf.LocationFinder(path);
	std::string locroot (loc.getPath());
	if (locroot.size() >= 1 && locroot[0] == '.')
		locroot = locroot.substr(1, locroot.size());
	path = path.substr(loc.getLocation_name().size(), path.size());
	fullpath[0] = web.getServ_Root() + locroot + "/" + path;
}

void	Cgi::setEnv(webServ& web, confData& conf)
{
	std::vector<std::string> header;
	splitstring(web.getReq().getHeader(), header, '\n');
	
	std::string req_head = web.getReq().getHeader();
	env.clear();
	std::string redirect_status = "REDIRECT_STATUS=200";
	env.push_back(redirect_status);
	std::string gateway_interface = "GATEWAY_INTERFACE=CGI/1.1";
	env.push_back(gateway_interface);
	std::string script_name = "SCRIPT_NAME=" + web.getReq().getUrl();
	env.push_back(script_name);
	std::string script_filename = "SCRIPT_FILENAME=" + fullpath[0];
	env.push_back(script_filename);
	std::string request_method = "REQUEST_METHOD=" + web.getReq().getMethod();
	env.push_back(request_method);
	std::string content_lenght = "CONTENT_LENGTH=" + std::to_string(body.size());
	env.push_back(content_lenght);
	std::string content_type = "CONTENT_TYPE=" + search_value_vect(header, "CONTENT_TYPE=");
	env.push_back(content_type);
	std::string path_info = "PATH_INFO=" + ;
	env.push_back(path_info);
	std::string path_translated = "PATH_TRANSLATED=" + ;
	env.push_back(path_translated);
	std::string query_string = "QUERY_STRING=" + ;
	env.push_back(query_string);
	std::string remoteaddr = "REMOTEaddr=" + ;
	env.push_back(remoteaddr);
	std::string remote_ident = "REMOTE_IDENT=" + ;
	env.push_back(remote_ident);
	std::string remote_user = "REMOTE_USER=" + ;
	env.push_back(remote_user);
	std::string request_uri = "REQUEST_URI=" + ;
	env.push_back(request_uri);
	std::string server_name = "SERVER_NAME=";
	if(search_value_vect(header, "Hostname=").size())
	{
		server_name += search_value_vect(header, "Hostname=");
	}
	else
	{
		server_name += web.getConf().getServName();
	}
	env.push_back(server_name);
	std::string server_port = "SERVER_PORT=" + web.getConf().getPort();
	env.push_back(server_port);
	std::string server_protocol = "SERVER_PROTOCOL=HTTP/1.1";
	env.push_back(server_protocol);
	std::string server_software = "SERVER_SOFTWARE=Webserv/1.0";
	env.push_back(server_software);
}
