/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:42:01 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/20 14:28:57 by chly-huc         ###   ########.fr       */
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

void Response::find_method(Request & req)
{
    std::cout << req.getMethod() << std::endl;
    if (req.getMethod() == "GET")
        getMethod(req);
    if (req.getMethod() == "DELETE")
        delMethod();
    if (req.getMethod() == "POST")
        postMethod();
}

void Response::getMethod(Request & req)
{
    version = req.getVersion();
    status = 200;
    stat_msg = "OK";
    body = readHTML(req.getUrl().c_str());
    content_lenght = itoa(strlen(body.c_str()));
    content_type = "text/html";
    
}

void Response::delMethod()
{

}

void Response::postMethod()
{

}

void Response::concat_response()
{
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