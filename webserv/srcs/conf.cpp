/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 05:49:14 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/20 17:17:18 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"

Conf::Conf()
{
    nbr_serv = 0;
}

Conf::~Conf()
{
        
}

Conf::Conf(const Conf & other)
{
    *this = other;
}

void Conf::print_info()
{
    for(int i = 0; i < nbr_serv; i++)
        (*confList)[i].print_info();
}



void Conf::verif_syntax(std::string str, std::string what)
{
    int i = -1;
    int count = 0;
    if (!what.compare("address"))
    {
        while(str[++i])
            if (str[i] == '.')
                count++;
        if (count != 3)
            printerr("Error with address syntax ...");
    }
    if (!what.compare("port"))
        while(str[++i])
            if (!isdigit(str[i]))
                printerr("Error with port syntax ...");
}

void Conf::parsing(char *path)
{
    confList = new std::vector<confData>(1);
    if (!(nbr_serv = (*confList)[0].parsing(path)))
        printerr("Error with parsing, 0 server found ...");
    std::cout << "sheeeeesh" << std::endl;
    confList = new std::vector<confData>(nbr_serv);
    for (int i = 0; i < nbr_serv; i++)
        (*confList)[i].scrapData();
    print_info();
    for(int i = 0; i < nbr_serv; i++)
    {
        verif_syntax((*confList)[i].getAdress(), "address");
        verif_syntax((*confList)[i].getPort(), "port");
    }
}