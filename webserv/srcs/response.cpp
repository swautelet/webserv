/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:42:01 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/31 16:09:58 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"

Response::Response()
{
    
}

Response::~Response()
{

}

Response::Response(const Response & other)
{
    *this = other;
}

Response &Response::operator=(Response const & other)
{
	return (*this);
}

void Response::find_method(Request & req, confData & conf)
{
    std::cout << req.getMethod() << std::endl;
    if (req.getMethod() == "GET")
        getMethod(req, conf);
    if (req.getMethod() == "DELETE")
        delMethod();
    if (req.getMethod() == "POST")
        postMethod();
}

int how_many(std::string str)
{
    int count = 0;
    int i = -1;
    while(str[++i])
        if(isspace(str[i]))
            count++;
    std::cout << count << std::endl;
    return count;
}
 
void Response::getMethod(Request & req, confData & conf)
{
    version = req.getVersion();
    status = 200;
    stat_msg = "OK";
    body = readHTML(conf, req.getUrl(), goodIndex(conf, req.getUrl()));
    content_lenght = itoa(body.size() + how_many(body));
    content_type = "text/html";
}

void Response::postMethod()
{
    
}

void Response::delMethod()
{

}

void Response::concat_response()
{
    std::cout << content_lenght << std::endl;
    full_response = version + ' ' + itoa(status) + ' ' + stat_msg + '\n' + "Content-Type: " + content_type + '\n' + "Content-Lenght: " + content_lenght + "\n\n" + body;
}

std::string Response::getResponse()
{
    return full_response;
}

std::string Response::getContentLenght()
{
    return content_lenght;
}

std::string Response::getContentType()
{
    return content_type;
}

std::string Response::getBody()
{
    return body;
}

std::string Response::getFullResponse()
{
    return full_response;
}

void Response::init()
{
    
}