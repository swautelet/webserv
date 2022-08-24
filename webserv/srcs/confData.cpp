/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 05:46:00 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/22 12:48:32 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"

std::string data_split;
std::string data;

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

const std::string& confData::getAdress() const
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

location& confData::LocationFinder(std::string str)
{
	std::string name = str.substr(0, str.find('/', 1));
    for (int i = 0; i < nbr_loc; i++)
        if (!(*loc)[i].getLocation_name().compare(name))
            return (*loc)[i];
    return (*loc)[0];
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


int confData::parsing(std::string path)
{
    std::ifstream fd;
    std::stringstream buff;
    fd.open(path, std::ifstream::in);
    if (!fd)
        printerr("Error with file opening ...");
    buff << fd.rdbuf();
    data = buff.str();
    check_quote(data);
    //data_split = server_split(data, "server ");
    
    std::cout << "mh\n";
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
    while(++x < nbr_loc)
    {
        (*loc)[x].print_info();
        j++;
    }
    std::cout << "--------------------------------------" << std::endl;
}

std::string location_str(std::string str)
{
    std::string tmp;
    
    if (str.find("location"))
        str = str.substr(str.find("location"), str.size());
    while(1)
    {
        tmp += str.substr(0, str.find("\n"));
        tmp += "\n";
        str = str.substr(str.find("\n") + 1, str.size());
        if (tmp.find("}") == std::string::npos)
            continue;
        else    
            break;
    }
    return tmp;
}

void confData::scrapData()
{
    int j;
    static int i = 0;
    int index = -1;
    std::string tmp;
    std::string cpy_data(data);
    while (!data.empty())
    {   
        tmp = data.substr(0, data.find("\n"));
        data = data.substr(data.find("\n") + 1, data.size());
        if (tmp.find("location") != std::string::npos)
            break;
        if (!tmp.find("server"))
                continue;
        else if (tmp.back() != ';')
            printerr("Error with conf file syntax ...");
        else if (tmp.find("listen")!= std::string::npos)
            setAddress(tmp);
        else if (tmp.find("server_name")!= std::string::npos)
            setServName(tmp);
        else if (tmp.find("root")!= std::string::npos)
            setPath(tmp);
        else if (tmp.find("methods")!= std::string::npos)
            setMethod(tmp);
        else if (tmp.find("error_page")!= std::string::npos)
            setErrorPage(tmp);
        else if (tmp.find("autoindex")!= std::string::npos)
            setAutoIndex(tmp);
        else if (tmp.find("index")!= std::string::npos)
            setIndex(tmp);
        else if (tmp.find("client_max_body_size")!= std::string::npos)
            setBodySize(tmp);
        else
            printerr("Something is wrong with your config file ...");
    }
    if (path.empty())
        path = "./";
    nbr_loc = check_server_nbr(cpy_data, "location ");
    std::cout << "Nbr of location : " << nbr_loc << std::endl;
    loc = new std::vector<location>(nbr_loc);
    for (int x = 0; x < nbr_loc; x++)
    {
        index = (*loc)[x].scrapData(location_str(cpy_data), index);
        cpy_data = cpy_data.substr(cpy_data.find("location") + 1, cpy_data.size());
    }
}
