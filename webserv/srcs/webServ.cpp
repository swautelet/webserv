/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:43:26 by chly-huc          #+#    #+#             */
/*   Updated: 2022/10/07 03:12:59 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webServ.hpp"

webServ::webServ()
{
    conf = new Conf;
	req = new Request;
	res = new Response;
	indexing = new Autodex;
	_cgi = new Cgi;
	max_body_size = 0;
}

webServ::webServ(std::string argv, char **envp)
{
	conf = new Conf;
	req = new Request;
	res = new Response;
	indexing = new Autodex;
	_cgi = new Cgi;
	max_body_size = 0;
	this->env = envp;

    conf->parsing(argv);
    sock.reserve(conf->getNbrServer());
	
	std::cout << "Nombre de server = " << conf->getNbrServer() << std::endl;
	for (unsigned long i = 0; i < conf->getNbrServer(); i++)
	{
		Socket next;
		sock.push_back(next);
	}
}

webServ::~webServ()
{
	delete conf;
	delete req;
	delete res;
	delete indexing;
}

webServ::webServ(webServ & other):conf(new Conf(other.getConf())), req(new Request(other.getReq())), res(new Response(other.getRes())), indexing(new Autodex(other.getAutodex())), serv_root(other.getServ_Root()), sock(other.getSock())
{
    
}

Conf & webServ::getConf()  
{
    return *conf;
}

std::vector<Socket> & webServ::getSock() 
{
    return sock;
}

Request & webServ::getReq()  
{
    return *req;
}

Response & webServ::getRes()  
{
    return *res;
}

Autodex & webServ::getAutodex()  
{
    return *indexing;
}
void	webServ::setServ_Root(char **env)
{
	std::string searched("PWD=");
	for (int i = 0; env[i]; i++)
	{
		std::string tmp(env[i]);
		if (!tmp.substr(0, searched.size()).compare(searched))
		{
			serv_root = tmp.substr(searched.size(), tmp.size());
			return;
		}
	}
}

const std::string&	webServ::getServ_Root() const 
{
	return serv_root;
}

Cgi& webServ::getCgi()
{
	return *_cgi;
}

std::pair<std::string, std::string> & webServ::getbool_redir()
{
    return bool_redir;
}

int webServ::getMax_body_size()
{
	return max_body_size;
}

void webServ::setbool_redir(std::vector<std::string> vec)
{
    std::string str;
    std::string loc;
    
    loc = vec.at(0);
    str = vec.at(1);
    bool_redir = std::make_pair(loc, str);
}

void webServ::setMax_body_size(int i)
{
	max_body_size = i;
}

void webServ::del_redir()
{
    bool_redir.first = "";
    bool_redir.second = "";
}

void webServ::cleave_info()
{
    max_body_size = 0;
    req->clear_info();
}

char ** webServ::getEnv()
{
	return env;
}
