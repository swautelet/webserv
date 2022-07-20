/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 05:46:00 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/20 15:49:46 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"

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

void confData::setAddress(std::string str)
{
    char **tmp;
    address = str.substr(strlen(" listen "), str.size());
    address.resize(address.size() - 1);
    tmp = ft_split((char*)address.c_str(), ':');
    address = tmp[0];
    port = tmp[1];
    free(tmp);
}

void confData::setPath(std::string str)
{
    path = str.substr(strlen(" root "), str.size());
    path.resize(path.size() - 1);
}

void confData::setServName(std::string str)
{
    serv_name = str.substr(strlen(" server_name "), str.size());
    serv_name.resize(serv_name.size() - 1);
}
void confData::setMethod(std::string str)
{
    method = str.substr(strlen(" methods "), str.size());
    method.resize(method.size() - 1);
}

int confData::parsing(char *path)
{
    std::ifstream fd;
    std::stringstream buff;
    const char *www = "conf";
    std::string data;
    fd.open(path, std::ifstream::in);
    if (!fd)
        printerr("Error with file opening ...");
    buff << fd.rdbuf();
    data = buff.str();
    check_quote(data);
    data_split = server_split(data, "server ");
    return check_server_nbr(data, "server ");
}

void confData::print_info()
{
    int x = -1;
    int j = -1;
    std::cout << "[Default]" << std::endl;
    std::cout << "Address->         " << "[" << address << "]" << std::endl;
    std::cout << "Port->            " << "[" << port << "]" << std::endl;
    std::cout << "Path->            " << "[" << path << "]" << std::endl;
    std::cout << "Serv_name->       " << "[" << serv_name << "]" << std::endl;
    std::cout << "Method->          " << "[" << method << "]" << std::endl << std::endl;
    while(++x < check_server_nbr(data_split[++j], "location "))
        loc[x].print_info();
    std::cout << "--------------------------------------" << std::endl;
}

void confData::scrapData()
{
    static int i = 0;
    int index = -1;
    int nbr_loc = 0;
    int j = 0;
    char **tmp;
    if(data_split[i])
    {
        tmp = ft_split(data_split[i], '\n');
        
        while (tmp[j] && !strnstr(tmp[j], "location ", strlen(tmp[j])))
        {
            if (strnstr(tmp[j], "listen ", strlen(tmp[j])))
                setAddress(tmp[j]);
            else if (strnstr(tmp[j], "root ", strlen(tmp[j])))
                setPath(tmp[j]);
            else if (strnstr(tmp[j], "server_name ", strlen(tmp[j])))
                setServName(tmp[j]);
            else if (strnstr(tmp[j], "methods ", strlen(tmp[j])))
                setMethod(tmp[j]);
            j++;
        }
        j = 0;
        nbr_loc = check_server_nbr(data_split[i], "location ");
        this->loc = new location[nbr_loc];
        for (int x = 0; x < nbr_loc; x++)
            index = loc[x].scrapData(data_split[i], index);
    }
    i++;
}
