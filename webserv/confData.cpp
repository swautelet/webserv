/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 05:46:00 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/18 14:15:27 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

char **data_split;

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

int confData::parsing(char *path)
{
    std::ifstream fd;
    std::stringstream buff;
    const char *www = "conf";
    std::string data;
    fd.open(path, std::ifstream::in);
    if (!fd)
    {
        printerr("Error with file opening ...");
        return -1;
    }
    buff << fd.rdbuf();
    data = buff.str();
    check_quote(data);
    data_split = server_split(data, "server ");
    return check_server_nbr(data);
}

void confData::setAddress(std::string str)
{
    address = str;
}

void confData::setPath(std::string str)
{
    path = str;
}
void confData::setServName(std::string str)
{
    serv_name = str;
}
void confData::setMethod(std::string str)
{
    method = str;
}
void confData::setIndex(std::string str)
{
    index = str;
}
void confData::scrapData()
{
    static int i = 0;
    int j = 0;
    char **tmp;
    if(data_split[i])
    {
        tmp = ft_split(data_split[i], '\n');
        while (tmp[j])
        {
            if (strnstr(tmp[j], "listen ", strlen(tmp[j])))
                setAddress(tmp[j]);
            else if (strnstr(tmp[j], "server_name ", strlen(tmp[j])))
                setServName(tmp[j]);
            j++;
        }
        j = 0;
    }
    i++;
}
