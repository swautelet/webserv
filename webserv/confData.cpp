/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 05:46:00 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/12 08:37:32 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

confData::confData()
{
    
}

confData::~confData()
{

}

confData::confData(const confData & other)
{
    *this = other;
}

std::string confData::getAdress()
{
    return address;
}

std::string confData::getPort()
{
    return port;
}
std::string confData::getPath()
{
    return path;
}

std::string confData::getServName()
{
    return serv_name;
}

std::string confData::getMethod()
{
    return method;
}

std::string confData::getIndex()
{
    return index;
}

void confData::parsing(char *path)
{
    std::ifstream fd;
    std::stringstream buff;
    const char *www = "conf";
    std::string data;
    fd.open(path, std::ifstream::in);
    if (!fd)
    {
        printerr("Error with file opening ...");
        return;
    }
    buff << fd.rdbuf();
    data = buff.str();
    check_quote(data);
    std::cout << check_server_nbr(data) << std::endl;
}
