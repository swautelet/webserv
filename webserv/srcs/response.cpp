/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:42:01 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/18 20:09:43 by chly-huc         ###   ########.fr       */
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

void Response::find_method(webServ & web, int i)
{
    std::cout << "find_method" << std::endl;
    std::cout << web.getReq().getMethod() << std::endl;
    if (web.getReq().getMethod() == "GET")
        MethodGet(web, web.getConf().getConflist(i));
    if (web.getReq().getMethod() == "DELETE")
        delMethod();
    if (web.getReq().getMethod() == "POST")
        postMethod();
}

void Response::setStatus(int status) // Todo : make the status code work
{
    this->status = status;
}

std::string Response::setStatMsg()
{
    if (status / 100 == 2)
        return "OK";
	else 
		return "KO";
}

void Response::setContentType(std::string fullpath)
{
	std:: cout << "i received fullpath =========== " << fullpath << std::endl;
	if (fullpath.rfind('.') != std::string::npos)
	{
		std::string type = fullpath.substr(fullpath.rfind(".") + 1, fullpath.size() - fullpath.rfind("."));
		std::cout << "looking for type of file with = " << type << std::endl;
		if (type == "html")
			content_type = "text/html";
		else if (type == "css")
			content_type = "text/css";
		else if (type == "js")
			content_type = "text/javascript";
		else if (type == "jpeg" || type == "jpg")
			content_type = "image/jpeg";
		else if (type == "png")
			content_type = "image/png";
		else if (type == "bmp")
			content_type = "image/bmp";
		else
			content_type = "text/plain";
	}
	else
		content_type = "text/plain";
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
 
void Response::MethodGet(webServ & web, confData & conf)
{
    version = web.getReq().getVersion();
    body = readHTML(web, conf, web.getReq().getUrl());
	setStatus(200);
    stat_msg = setStatMsg();
    content_lenght = itoa(body.size() + how_many(body));
	std::cout << "data_type possible ------------------" << std::endl << std::endl;
	for (int i = 0; i < web.getReq().getDataType().size(); i++)
	{
		std::cout << web.getReq().getDataType()[i] << std::endl;
	}
   // setContentType(web.getReq().getDataType()[0]);
}

void Response::postMethod()
{
    
}

void Response::delMethod()
{

}

void Response::concat_response()
{
    std::cout << "header response  ========" << std::endl << std::endl <<  version + ' ' + itoa(status) + ' ' + stat_msg + '\n' + "Content-Type: " + content_type + '\n' + "Content-Lenght: " + content_lenght + "\n" << std::endl;
	full_response = version + ' ' + itoa(status) + ' ' + stat_msg + '\n' + "Content-Type: " + content_type + '\n' + "Content-Lenght: " + content_lenght + "\n\n" + body;
//	std::cout << "full_response ---------------------------" << std::endl << std::endl << full_response << std::endl << std::endl;
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
