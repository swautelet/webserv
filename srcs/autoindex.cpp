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
    
}

Autodex::Autodex(const Autodex & other):index_str(other.getIndexStr())
{
//    *this = other;
    std::cout << "Autodex destructor called" << std::endl;
}

Autodex& Autodex::operator=(const Autodex& other)
{
	index_str = other.getIndexStr();
	return *this;
}

std::string Autodex::create_dex(webServ & web, confData & conf, std::string url, const location & loc)
{
    DIR *dir;
    (void)web;
    (void)conf;
    (void)loc;
    (void)dir;
    
    int i = -1;
    (void)i;
    std::string full_url(url);
    std::string index_str;
    std::string loca = location_exe(conf, url);;

    if ((dir = opendir(full_url.data())) != NULL)
        index_str = html_creation(dir, full_url, loca, web.getReq().getUrl());
    web.getRes().setContentType(".html");
    return index_str;
}

std::string Autodex::html_creation(DIR *dir, std::string full_url, std::string loca, std::string url)
{
    (void)loca;
    (void)full_url;
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
            if (download == 1)
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
    closedir(dir);
    return tmp;
}

std::string Autodex::getIndexStr() const 
{
    return index_str;
}