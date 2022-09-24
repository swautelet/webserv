/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:02:42 by chly-huc          #+#    #+#             */
/*   Updated: 2022/09/24 11:57:38 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "location.hpp"

location::location()
{
    autoindex = 0;
}

location::~location()
{

}

location::location(const location & other):path(other.getPath()), method(other.getMethod()), error_page(other.getErrorPage()), index(other.getIndex()), location_name(other.getLocation_name()), body_size(other.getBodySize()), autoindex(other.getAutoIndex())
{
    
}

location& location::operator=(const location& other)
{
	path = other.getPath();
	method = other.getMethod();
	error_page = other.getErrorPage();
	index = other.getIndex();
	location_name = other.getLocation_name();
	body_size = other.getBodySize();
	autoindex = other.getAutoIndex();
	return *this;
}

std::string location::getPath() const
{
    return path;
}

std::vector<std::string> location::getIndex() const
{
    return index;
}

std::string location::getMethod() const
{
    return method;   
}

std::string location::getLocation_name() const
{
    return location_name;   
}

std::string location::getErrorPage() const
{
    return location_name;   
}

std::string location::getBodySize() const
{
    return body_size;   
}

int location::getAutoIndex() const
{
    return autoindex;
}

const std::vector<std::string> & location::getRedir() const
{
    return redir;
}

void location::setLocation_name(std::string& str)
{
    remove_spaces(str);
    location_name = str.substr(str.find("location ") + strlen("location "), str.size());
}

void location::setPath(std::string str)
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
void location::setMethod(std::string str)
{
    remove_spaces(str);
    method = str.substr(strlen("methods "), str.size());
    if (method.empty())
        return;
    method.resize(method.size() - 1);
}

void location::setIndex(std::string str)
{
    if (!index.empty())
        index.clear();
    std::string tmp;
    remove_spaces(str);
    str = str.substr(str.find(" ") + 1, str.size());
    while(str.find(" ") != std::string::npos)
    {
        tmp = str.substr(0, str.find(" "));
        index.push_back(tmp);
        str = str.substr(str.find(" ") + 1, str.size());
    }
	str = str.substr(0, str.size() - 1);
    index.push_back(str);
    if (index.back().empty())
        return;
//    index.resize(index.size());
}

void location::setErrorPage(std::string str)
{
    remove_spaces(str);
    error_page = str.substr(strlen("error_page "), str.size());
    if (error_page.empty())
        return;
    error_page.resize(error_page.size() - 1); 
}

void location::setBodySize(std::string str)
{
    remove_spaces(str);
    body_size = str.substr(strlen("client_max_body_size "), str.size());
    if (body_size.empty())
        return;
    body_size.resize(body_size.size() - 1);
}

void location::setAutoIndex(std::string str)
{
    remove_spaces(str);
    if (!str.compare("autoindex on;"))
        autoindex = 1;
    else if (!str.compare("autoindex off;"))
        autoindex = 0;
}

void location::setRedir(std::string str)
{
    if (!redir.empty())
        redir.clear();
    std::string tmp;
    remove_spaces(str);
    str = str.substr(str.find(" ") + 1, str.size());
    while(str.find(" ") != std::string::npos)
    {
        tmp = str.substr(0, str.find(" "));
        if (tmp.find("^") != std::string::npos)
        {
            if (!tmp.compare("^"))
                std::cout << "kekw" << std::endl;
            if (!tmp.compare("^"))
                tmp = "/";
            else
                tmp.erase(0, 1);
        }
        std::cout << "tmp.. " << tmp << std::endl;
        redir.push_back(tmp);
        if (str.empty())
            return;
        str = str.substr(str.find(" ") + 1, str.size());
    }
	str = str.substr(0, str.size() - 1);
    redir.push_back(str);
    if (redir.back().empty())
        return;
}

void location::edit_info(std::string str, std::string info, std::vector<std::string> vec)
{
    if (!str.compare("path"))
        path = info;
    if (!str.compare("method"))
        method = info;
    if (!str.compare("error_page"))
        error_page = info;
    if (!str.compare("autoindex"))
        autoindex = atoi(info.c_str());
    if (!str.compare("index"))
        index = vec;
    if (!str.compare("body_size"))
        body_size = info;
    if (!str.compare("redir"))
        redir = vec;
}

void location::print_info() const
{
    if (!location_name.empty())
        std::cout << "[location " << location_name << "]" << std::endl;
    if (!path.empty())
        std::cout << "Path->            " << "[" << path << "]" << std::endl;
    if (!method.empty())
        std::cout << "Method->          " << "[" << method << "]" << std::endl;
    if (!index.empty())
    {
        std::cout << "Index->           ";
        for (unsigned long i = 0; i < index.size(); i++)
		{
            std::cout << "[" << index[i] << "]";
		}
        std::cout << std::endl;
    }
    if (!redir.empty())
    {
        std::cout << "redir->           ";
        for (unsigned long i = 0; i < redir.size(); i++)
		{
            std::cout << "[" << redir[i] << "]";
		}
        std::cout << std::endl;
    }
    if (!error_page.empty())
        std::cout << "Error_page->      " << "[" << error_page << "]" << std::endl;
    if (!body_size.empty())
        std::cout << "Body_size->       " << "[" << body_size << "]" << std::endl;
    std::cout << "AutoIndex->       " << "[" << autoindex << "]" << std::endl << std::endl;
}

int location::scrapData(std::string data, int i)
{
    (void)i;
    std::string tmp;
    tmp = data.substr(0, data.find("\n"));
    setLocation_name(tmp);
    while (!data.empty())
    {
        tmp = data.substr(0, data.find("\n"));
        // std::cout << "tmp in loc == " << tmp << std::endl;
        data = data.substr(data.find("\n") + 1, data.size());
        if (tmp.find("server {") != std::string::npos)
            break;
        if (str_isspace(tmp))
            continue;
        if (tmp.find("{") != std::string::npos || tmp.find("location")!= std::string::npos)
            continue;
        if (tmp.find("}") != std::string::npos)
            break;
        if (tmp.size() >= 1 && tmp[tmp.size() - 1] != ';')
            printerr("Error with conf file syntax ...");
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
        else if (tmp.find("return")!= std::string::npos)
            setRedir(tmp);
        else
            printerr("Something is wrong with your config file ...");
    }
    if (data.find("server") != std::string::npos)
        data = data.substr(data.find("server"), data.size());
    if (path.empty())
        path = "./";
    return 0;
}
