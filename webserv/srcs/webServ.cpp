/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:43:26 by chly-huc          #+#    #+#             */
/*   Updated: 2022/08/18 20:01:13 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"

webServ::webServ()
{
    conf = new Conf;
	req = new Request;
	res = new Response;
	indexing = new Autodex;
}


webServ::webServ(std::string argv)
{
	conf = new Conf;
	req = new Request;
	res = new Response;
	indexing = new Autodex;

    conf->parsing(argv);
    sock.reserve(conf->getNbrServer());
	std::cout << "nombre de server = " << conf->getNbrServer() << std::endl;
	for (unsigned long i = 0; i < conf->getNbrServer(); i++)
	{
		Socket* next = new Socket;
		sock.push_back(*next);
	}
}

webServ::~webServ()
{
	for (std::vector<Socket>::iterator iter = sock.begin(); iter != sock.end() - 1; iter++)
	{
		delete &(*iter);
	}
	delete conf;
	delete req;
	delete res;
	delete indexing;
}

webServ::webServ(webServ & other):conf(new Conf(other.getConf())), req(new Request(other.getReq())), res(new Response(other.getRes())), sock(other.getSock()), indexing(new Autodex(other.getAutodex()))
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
