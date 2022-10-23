/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:45:19 by chly-huc          #+#    #+#             */
/*   Updated: 2022/09/27 19:16:31 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autoindex.hpp"

Autodex::Autodex()
{
    
}

Autodex::~Autodex()
{
    std::cout << "Autodex destructor called" << std::endl;
}

Autodex::Autodex(const Autodex & other):index_str(other.getIndexStr())
{
//    *this = other;
}

Autodex& Autodex::operator=(const Autodex& other)
{
	index_str = other.getIndexStr();
	return *this;
}

std::string Autodex::create_dex(webServ & web, std::string url)
{
    DIR *dir;
    std::string full_url(url);
    std::string index_str;

    if ((dir = opendir(full_url.data())) != NULL)
    {
        index_str = html_creation(dir, web.getReq().getUrl());
        closedir(dir);
    }
    web.getRes().setContentType(".html");
    return index_str;
}

std::string Autodex::html_creation(DIR *dir, std::string url)
{
    struct dirent *ent;
    int download = 0;
    std::string tmp;
    tmp += "<html>";
	tmp += "<head><title>Index of ";
	tmp += url + "</title></head>\n";
	tmp += "<body>\n";
	tmp += "<h1>Index of ";
	tmp += url + "</h1><hr><pre>";
    if (!url.substr(url.rfind("/") + 1, url.size()).compare("download"))
        download = 1;
    while ((ent = readdir(dir)) != NULL)
	{
		if (strcmp(ent->d_name, ".") != 0)
		{
			tmp += "<a href=\"";
			tmp += url;
			if (url[url.size() - 1] != '/')
				tmp += '/';
			tmp += ent->d_name;
            if (download == 1 && strcmp(ent->d_name, ".."))
                tmp += "\"download";
            else
                tmp += "\"";
			tmp += ">";
			tmp += ent->d_name;
			tmp += " </a>\n";
		}
	}
	tmp += "</pre><hr></body>";
	tmp += "</html>";
    return tmp;
}

std::string Autodex::getIndexStr() const 
{
    return index_str;
}