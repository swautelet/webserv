/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:02:50 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/01 05:17:24 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

Request::Request()
{
    
}

Request::~Request()
{

}

Request::Request(const Request & other)
{
    *this = other;
}
            
void Request::getInfo(int connection)
{
    char **req;
    char **req2;
    char buff[10000];
    auto bytesRead = read(connection, buff, 100);
    
    req = ft_split(buff, '\n');
    req2 = ft_split(req[0], ' ');
    if (!strcmp(req2[0],"GET") || !strcmp(req2[0],"POST") || !strcmp(req2[0],"DELETE"))
        method = req2[0];
    url = req2[1];
    version = req2[2];
    version.resize(strlen(version.c_str()) - 1);
    return;
}

std::string Request::getUrl()
{
    return url;
}

std::string Request::getMethod()
{
    return method;
}
std::string Request::getVersion()
{
    return version;
}
std::string Request::getHeader()
{
    return header;
}