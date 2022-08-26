/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 05:49:14 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/22 11:07:05 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"

Conf::Conf():confList(1)
{
    nbr_serv = 0;
}

Conf::~Conf()
{
        
}

Conf::Conf(const Conf & other)
{
	nbr_serv = other.getNbrServer();
	confList.reserve(nbr_serv);
	while (confList.size() < nbr_serv)
	{
		confData next;
		confList.push_back(next);
	}
	confList = other.getVectorConflist();
}

void Conf::print_info()
{
    for(int i = 0; i < nbr_serv; i++)
        (confList)[i].print_info();
}

std::string Conf::getAddress(int index) const
{
    return (confList)[index].getAdress();
}

std::string Conf::getPort(int index) const
{
    return (confList)[index].getPort();
}

std::string Conf::getPath(int index) const
{
    return (confList)[index].getPath();
}
std::string Conf::getServName(int index) const
{
    return (confList)[index].getServName();  
}
std::string Conf::getMethod(int index) const
{
    return (confList)[index].getMethod();     
}
std::vector<std::string> Conf::getIndex(int index) const
{
    return (confList)[index].getIndex();
}

int Conf::getNbrServer() const
{
    return nbr_serv;
}

confData & Conf::getConflist(int index) 
{
    return (confList)[index];
}

void Conf::parsing(std::string path)
{
    if (!(nbr_serv = (confList)[0].parsing(path)))
        printerr("Error with parsing, 0 server found ...");
    confList.reserve(nbr_serv);
	while (confList.size() < nbr_serv)
	{
		confData next;
		confList.push_back(next);
	}
    for (int i = 0; i < nbr_serv; i++)
        (confList)[i].scrapData();
    std::cout << "nbr_serv == " <<nbr_serv << std::endl;
    print_info();
}

const std::vector<confData> Conf::getVectorConflist() const
{
	return confList;
}
