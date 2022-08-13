/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:02:42 by chly-huc          #+#    #+#             */
/*   Updated: 2022/08/13 21:53:41 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"

location::location()
{
    location_name = "";
    path = "";
    method = "";
    index = "";
    autoindex = 0;
}

location::~location()
{

}

location::location(const location & other)
{
    
}

std::string location::getPath()
{
    return path;
}

std::string location::getIndex()
{
    return index;
}

std::string location::getMethod()
{
    return method;   
}

std::string location::getLocation_name()
{
    return location_name;   
}

std::string location::getErrorPage()
{
    return location_name;   
}

std::string location::getBodySize()
{
    return body_size;   
}

int location::getAutoIndex()
{
    return autoindex;
}


void location::setLocation_name(std::string str)
{
    remove_spaces(str);
    location_name = str.substr(strlen("location "), str.size());
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
    remove_spaces(str);
    index = str.substr(strlen("index "), str.size());
    if (index.empty())
        return;
    index.resize(index.size() - 1);
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

void location::print_info()
{
    if (!location_name.empty())
        std::cout << "[location " << location_name << "]" << std::endl;
    if (!path.empty())
        std::cout << "Path->            " << "[" << path << "]" << std::endl;
    if (!method.empty())
        std::cout << "Method->          " << "[" << method << "]" << std::endl;
    if (!index.empty())
        std::cout << "Index->           " << "[" << index << "]" << std::endl;
    if (!error_page.empty())
        std::cout << "Error_page->      " << "[" << error_page << "]" << std::endl;
    if (!body_size.empty())
        std::cout << "Body_size->       " << "[" << body_size << "]" << std::endl;
    std::cout << "AutoIndex->       " << "[" << autoindex << "]" << std::endl << std::endl;
}
int location::scrapData(char *str, int i)
{
    char **tmp;
    int x = 0;

    tmp = ft_split(str, '\n');
    while (tmp[++i])
    {   
        if (strnstr(tmp[i], "location ", strlen(tmp[i])))
        {
            autoindex = 0;
            setLocation_name(tmp[i]);
            i++;
            while (tmp[i] && !strnstr(tmp[i], "}", strlen(tmp[i])))
            {
                if (strnstr(tmp[i], "root", strlen(tmp[i])))
                    setPath(tmp[i]);
                else if (strnstr(tmp[i], "methods", strlen(tmp[i])))
                    setMethod(tmp[i]);
                else if (strnstr(tmp[i], "error_page", strlen(tmp[i])))
                    setErrorPage(tmp[i]);
                else if (strnstr(tmp[i], "autoindex", strlen(tmp[i])))
                    setAutoIndex(tmp[i]);
                else if (strnstr(tmp[i], "index", strlen(tmp[i])))
                    setIndex(tmp[i]);
                else if (strnstr(tmp[i], "client_max_body_size", strlen(tmp[i])))
                    setBodySize(tmp[i]);
                else if (strnstr(tmp[i], "{", strlen(tmp[i])))
                    (void)NULL;
                else
                    printerr("Something is wrong with your config file ...");
                i++;
            }
            return i;
        }
        if (path.empty())
            path = "./";
    }
    return i;
}