#include "header.hpp"

#define BUFF_SIZE 50

std::string start_script(webServ web, std::string path, char **arg, char **env)
{
	(void)web;
	int pip[2];
	int id;
	int status;
	int ret;
	std::string response = "";
	char buffer[BUFF_SIZE + 1];
	pipe(pip);
	id = fork();
	if (id == -1)
	{
		std::cout << "could'nt fork" << std::endl;
		return response;
	}
	if (id == 0)
	{
		dup2(0, pip[0]);
		if (execve(path.c_str(), arg, env) < 0)
		{
			std::cout << "Script couldn't be loaded" << std::endl;
			exit(0);
		}
	}
	else
	{
		wait(&status);
		while((ret = read(pip[1], buffer, BUFF_SIZE)) > 0)
		{
			std::string tmp(buffer);
			response += tmp.substr(0, ret);
		}
	}
	return response;
}
