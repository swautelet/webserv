/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 05:49:14 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/20 15:39:08 by chly-huc         ###   ########.fr       */
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

void Conf::parsing(char *path)
{
    nbr_serv = (*confList)[0].parsing(path);
    confList = new std::vector<confData>(nbr_serv);
    for (int i = 0; i < nbr_serv; i++)
        (*confList)[i].scrapData();
    print_info();
}