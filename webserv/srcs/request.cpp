/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:02:50 by shyrno            #+#    #+#             */
/*   Updated: 2022/09/27 19:19:35 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"

Request::Request()
{
    
}

Request::~Request()
{
    type_data.clear();
}

Request::Request(const Request & other):method(other.getMethod()), url(other.getUrl()), version(other.getVersion()), header(other.getHeader()), body(other.getBody()), type_data(other.getDataType())
{
    
}
   
Request& Request::operator=(const Request& other)
{
	method = other.getMethod();
	url = other.getUrl();
	version = other.getVersion();
	header = other.getHeader();
	body = other.getBody();
	type_data = other.getDataType();
	return *this;
}

int Request::getInfo(int connection)
{
    std::vector<std::string> req, req2;
    std::string string;
    int ret;
    char buff[10000];
    
    if ((ret = recv(connection, buff, sizeof(buff), 0)) < 0)
        printerr("Error with recv ...");
	if (ret == 0)
       return 0;
    string = buff;
 	splitstring(buff, req, '\n');
	splitstring(req[0], req2, ' ');
    if (!req2[0].compare("GET") || !req2[0].compare("POST") || !req2[0].compare("DELETE"))
        method = req2[0];
    url = req2[1];
    version = req2[2];
    version.resize(strlen(version.c_str()) - 1);
	type_data.clear();
    _search_info(req, string);
    if (url.find("?") != std::string::npos)
    {
        query_s = url.substr(url.find("?") + 1, url.size());
        url = url.substr(0 ,url.find("?"));
        std::cout << " BUT " << query_s << std::endl;
    }
    std::cout << "Header is : " << header << std::endl;
    return 1;
}

void Request::_search_info(std::vector<std::string> req, std::string buff)
{
    
    std::string str;
    std::string searched = "Accept: ";
    for (unsigned long i = 0; i < req.size(); i++)
    {
        str = req[i];
        if (!str.substr(0, searched.size()).compare(searched))
        {
			splitstring(str.substr(searched.size(), str.size()), type_data, ',');
            break ;
        }
    }
    content_lenght = search_value_vect(req, "Content-Length:");
    int index;
    while(buff.find("\n") != std::string::npos)
    {
        std::string tmp_2;
        index = buff.find("\n");
        tmp_2 = buff.substr(0, index);
        if (tmp_2.empty())
        {
            print("Body , or not has been found");
            break;
        }
        header += tmp_2 + "\n";
        buff = buff.substr(index + 1, buff.size());
    }
    body = buff;
    
}

std::string Request::getUrl() const 
{
    return url;
}

std::string Request::getMethod() const 
{
    return method;
}

std::string Request::getVersion() const 
{
    return version;
}

std::string Request::getHeader() const 
{
    return header;
}

const std::vector<std::string>&	Request::getDataType() const
{
	return type_data;
}

std::string Request::getBody() const 
{
    return body;
}

std::string Request::getContentLenght() const
{
    return content_lenght;
}

void Request::clear_info()
{
    header = "";
    url = "";
    body = "";
    version = "";
    query_s = "";
}

std::string Request::getQuery_string()
{
    return query_s;
}