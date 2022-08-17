/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 05:46:00 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/17 16:16:11 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"

char **data_split;

confData::confData()
{
    autoindex = 0;
    nbr_loc = 0;
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

std::vector<std::string> confData::getIndex()
{
    return index;
}

std::string confData::getErrorPage()
{
    return error_page;
}

std::string confData::getBodySize()
{
    return body_size;
}

int confData::getLocationNbr()
{
    return nbr_loc;
}

int confData::getAutoIndex()
{
    return autoindex;
}

location & confData::getLocation(int index)
{
    return (*loc)[index];
}

location & confData::getGoodLocation(std::string str)
{
    for (int i = 0; i < nbr_loc; i++)
        if (!(*loc)[i].getLocation_name().compare(str))
            return (*loc)[i];
    return (*loc)[0];
}

int confData::LocationFinder(std::string str)
{
    for (int i = 0; i < nbr_loc; i++)
        if (!(*loc)[i].getLocation_name().compare(str))
            return 1;
    return 0;
}

void confData::setAddress(std::string str)
{
    char **tmp;
    remove_spaces(str);
    address = str.substr(strlen("listen "), str.size());
    if (address.empty() || address.find(":") == std::string::npos)
        return;
    address.resize(address.size() - 1);
    tmp = ft_split((char*)address.c_str(), ':');    
    address = tmp[0];
    port = tmp[1];
    free(tmp);
}

void confData::setPath(std::string str)
{
    remove_spaces(str);
    path = str.substr(strlen("root "), str.size());
    if (path.empty())
    {
        path = "./";
        return;
    }
    path.resize(path.size() - 1);
}

void confData::setServName(std::string str)
{
    remove_spaces(str);
    serv_name = str.substr(strlen("server_name "), str.size());
    if (serv_name.empty())
        return;
    serv_name.resize(serv_name.size() - 1);
}
void confData::setMethod(std::string str)
{
    remove_spaces(str);
    method = str.substr(strlen("methods "), str.size());
    if (method.empty())
        return;
    method.resize(method.size() - 1);
}

void confData::setErrorPage(std::string str)
{
    remove_spaces(str);
    error_page = str.substr(strlen("error_page "), str.size());
    if (error_page.empty())
        return;
    error_page.resize(error_page.size() - 1);
}

void confData::setIndex(std::string str)
{
    std::string tmp;
    remove_spaces(str);
    str = str.substr(str.find(" "), str.size());
    while(str.find(" ") != std::string::npos)
    {
        tmp = str.substr(0, str.find(" "));
        index.push_back(tmp);
        if (str.empty())
            return;
        str = str.substr(str.find(" ") + 1, str.size());
    }
    index.push_back(str);
    if (index.back().empty())
        return;
    index.resize(index.size() - 1);
}

void confData::setAutoIndex(std::string str)
{
    remove_spaces(str);
    if (!str.compare("autoindex on;"))
        autoindex = 1;
    else if (!str.compare("autoindex off;"))
        autoindex = 0;
}

void confData::setBodySize(std::string str)
{
    remove_spaces(str);
    body_size = str.substr(strlen("client_max_body_size "), str.size());
    if (body_size.empty())
        return;
    body_size.resize(body_size.size() - 1);
}


int confData::parsing(char *path)
{
    std::ifstream fd;
    std::stringstream buff;
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
    int i = -1;
    int j = 0;
    std::cout << "[Default]" << std::endl;
    if (!address.empty())
        std::cout << "Address->         " << "[" << address << "]" << std::endl;
    if (!port.empty())
        std::cout << "Port->            " << "[" << port << "]" << std::endl;
    if (!path.empty())
        std::cout << "Path->            " << "[" << path << "]" << std::endl;
    if (!serv_name.empty())
        std::cout << "Serv_name->       " << "[" << serv_name << "]" << std::endl;
    else
        std::cout << "Serv_name->       " << "[..........]" << std::endl;
    if (!index.empty())
    {
        std::cout << "Index->           ";
        while (++i < index.size())
            std::cout << "[" << index[i] << "]";
        std::cout << std::endl;
    }
    if (!method.empty())
        std::cout << "Method->          " << "[" << method << "]" << std::endl;
    if (!error_page.empty())
        std::cout << "Error_page->      " << "[" << error_page << "]" << std::endl;
    if (!body_size.empty())
        std::cout << "Body->            " << "[" << body_size << "]" << std::endl;
    std::cout << "Autoindex->       " << "[" << autoindex << "]" << std::endl;
    while(data_split[j] && ++x < check_server_nbr(data_split[j], "location "))
    {
        (*loc)[x].print_info();
        j++;
    }
    std::cout << "--------------------------------------" << std::endl;
}

void confData::scrapData()
{
    int j;
    static int i = 0;
    int index = -1;
    char **tmp;
    if (data_split[i])
    {
        j = -1;
        tmp = ft_split(data_split[i], '\n');
        while (tmp[++j] && !strnstr(tmp[j], "location ", strlen(tmp[j])))
        {
            
            std::string semicolon(tmp[j]);
            if (strnstr(tmp[j], "server", strlen(tmp[j])))
                continue;
            else if (semicolon.back() != ';')
                printerr("Error with conf file syntax ...");
            else if (strnstr(tmp[j], "listen", strlen(tmp[j])))
                setAddress(tmp[j]);
            else if (strnstr(tmp[j], "server_name", strlen(tmp[j])))
                setServName(tmp[j]);
            else if (strnstr(tmp[j], "root", strlen(tmp[j])))
                setPath(tmp[j]);
            else if (strnstr(tmp[j], "methods", strlen(tmp[j])))
                setMethod(tmp[j]);
            else if (strnstr(tmp[j], "error_page", strlen(tmp[j])))
                setErrorPage(tmp[j]);
            else if (strnstr(tmp[j], "autoindex", strlen(tmp[j])))
                setAutoIndex(tmp[j]);
            else if (strnstr(tmp[j], "index", strlen(tmp[j])))
                setIndex(tmp[j]);
            else if (strnstr(tmp[j], "client_max_body_size", strlen(tmp[j])))
                setBodySize(tmp[j]);
            else
                printerr("Something is wrong with your config file ...");
        }
        if (path.empty())
            path = "./";
        nbr_loc = check_server_nbr(data_split[i], "location ");
        loc = new std::vector<location>(nbr_loc);
        for (int x = 0; x < nbr_loc; x++)
            index = (*loc)[x].scrapData(data_split[i], index);
    }
    i++;
}
