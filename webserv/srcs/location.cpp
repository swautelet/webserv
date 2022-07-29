/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:02:42 by chly-huc          #+#    #+#             */
/*   Updated: 2022/07/29 18:17:42 by chly-huc         ###   ########.fr       */
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

int location::getAutoIndex()
{
    return autoindex;
}


void location::setLocation_name(std::string str)
{
    location_name = str.substr(strlen(" location "), str.size());
}

void location::setPath(std::string str)
{
    path = str.substr(strlen("  root "), str.size());
    path.resize(path.size() - 1);
}
void location::setMethod(std::string str)
{
    method = str.substr(strlen("  methods "), str.size());
    method.resize(method.size() - 1);
}
void location::setIndex(std::string str)
{
    index = str.substr(strlen("  index "), str.size());
    index.resize(index.size() - 1);
}

void location::print_info()
{
    // if (!location_name.empty())
    //     std::cout << "[location " << location_name << "]" << std::endl;
    // if (!path.empty())
    //     std::cout << "Path->            " << "[" << path << "]" << std::endl;
    // if (!method.empty())
    //     std::cout << "Method->          " << "[" << method << "]" << std::endl;
    // if (!index.empty())
    //     std::cout << "Index->           " << "[" << index << "]" << std::endl;
    // std::cout << "AutoIndex->       " << "[" << autoindex << "]" << std::endl << std::endl;
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
            if (tmp[++i])
            {
                while (tmp[i] && !strnstr(tmp[i], "}", strlen(tmp[i])))
                {
                    if (strnstr(tmp[i], "root ", strlen(tmp[i])))
                        setPath(tmp[i]);
                    else if (strnstr(tmp[i], "methods ", strlen(tmp[i])))
                        setMethod(tmp[i]);
                    else if (strnstr(tmp[i], "autoindex on", strlen(tmp[i])))
                        autoindex = 1;
                    else if (strnstr(tmp[i], "index ", strlen(tmp[i])))
                        setIndex(tmp[i]);
                    i++;
                }
            }
            return i;
        }
    }
    return i;
}