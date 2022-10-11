/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:02:50 by shyrno            #+#    #+#             */
/*   Updated: 2022/10/11 01:39:40 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"

Request::Request()
{
    brutbody = tmpfile();
}

Request::~Request()
{
    type_data.clear();
}

Request::Request(const Request & other):method(other.getMethod()), url(other.getUrl()), version(other.getVersion()), header(other.getHeader()), body(other.getBody()), type_data(other.getDataType())
{
    brutbody = tmpfile();
}
   
Request& Request::operator=(const Request& other)
{
	method = other.getMethod();
	url = other.getUrl();
	version = other.getVersion();
	header = other.getHeader();
	body = other.getBody();
	type_data = other.getDataType();
    brutbody = tmpfile();
	return *this;
}

int Request::getInfo(int connection, std::string string)
{
    (void)connection;
    std::cout << string << std::endl;
    clear_info();
    std::vector<std::string> req, req2;

    //string = buff;
 	splitstring(string, req, '\n');
	splitstring(req[0], req2, ' ');
    if (!req2[0].compare("GET") || !req2[0].compare("POST") || !req2[0].compare("DELETE"))
        method = req2[0];
    url = req2[1];
    version = req2[2];
    version.resize(strlen(version.c_str()) - 1);
	type_data.clear();
    _search_info(req, string);
    lseek(fileno(brutbody), 0, SEEK_SET);
    char* temp = (char*)body.data();
    write(fileno(brutbody), temp, atoi(content_length.c_str()));
    lseek(fileno(brutbody), 0, SEEK_SET);
    if (url.find("?") != std::string::npos)
    {
        query_s = url.substr(url.find("?") + 1, url.size());
        url = url.substr(0 ,url.find("?"));
        std::cout << " BUT " << query_s << std::endl;
    }
    clean_header();
    std::cout << std::endl << "Header is ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << std::endl << header << std::endl << "-----------------------------------------------------------------------" << std::endl;
    std::cout << "BODY IS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << std::endl << body << std::endl << "--------------------------------------------------------------" << std::endl;
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
    content_length = search_value_vect(req, "Content-Length:");
    content_type = search_value_vect(req, "Content-Type:");
    if (content_length.empty())
        content_length = "0";
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
    if (!content_length.empty())
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

std::string Request::getContentType() const 
{
    return content_type;
}

std::string Request::getContentLength() const
{
    return content_length;
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
int Request::getBrutbody_fileno()
{
    return fileno(brutbody);
}

void    Request::clean_header()
{
    unsigned long decal = 0;
    for (unsigned long i = 0; i + decal < header.size(); i++)
    {
        if (header[i + decal] == '\r')
            decal++;
        if (decal)
            header[i] = header[i + decal];
    }
    header.resize(header.size() - decal);
    if (header[header.size() - 2] == '\n' && header[header.size() - 1] == '\n')
        header.resize(header.size() - 1);
}
