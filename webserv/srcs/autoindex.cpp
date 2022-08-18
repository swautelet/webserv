/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:45:19 by chly-huc          #+#    #+#             */
/*   Updated: 2022/08/18 22:26:45 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"

Autodex::Autodex()
{
    
}

Autodex::~Autodex()
{
            
}

Autodex::Autodex(const Autodex & other)
{
    *this = other;
}

std::string Autodex::create_dex(webServ & web, confData & conf, std::string url)
{
    DIR *dir;
    
    struct dirent *ent;
    struct stat info;
    std::ofstream out;
    std::string path;
    std::string tmp;
    int i = -1;
    int autodex = 0;

    std::cout << "--------------AUTOINDEX CREATION---------------" << std::endl;
    if (web.getReq().getUrl().size() > 1)
        path = web.getReq().getUrl().substr(1, web.getReq().getUrl().size());
    else
        path = web.getReq().getUrl();
    std::cout << "!!!!!!!!!!!!!!PATH == " << path << std::endl;
    std::cout << "*---------------------------------------------*url == " << url << std::endl;
    if (stat(path.c_str(), &info) != 0)
        std::cout << "AH\n";
    while(++i < conf.getLocationNbr())
    {
        if (!conf.getLocation(i).getLocation_name().compare(path))
        {
            std::cout << "---- " << conf.getLocation(i).getLocation_name() << std::endl;
            std::cout << "---- " << conf.getLocation(i).getAutoIndex() << std::endl;
            autodex = conf.getLocation(i).getAutoIndex();
            path = conf.getGoodLocation(path).getPath();
            break;
        }
    }
    if ((dir = opendir(url.c_str())) != NULL)
    {
        tmp += "<html><head><title>Index of " + url + "</title></head>\n<body><h1>Index of </h1><hr><pre>" ;
        while ((ent = readdir(dir)) != NULL)
        {
            if (strcmp(ent->d_name, "."))
            {
                std::cout << "---- " << url << std::endl;
                tmp += "<a href=";
                if (!strcmp(ent->d_name, ".."))
                    tmp += url.substr(0, url.rfind("/"));
                else
				    tmp += url;
				if (url[url.size() - 1] != '/')
					tmp += '/';
				tmp += ent->d_name;
				tmp += ">";
				tmp += ent->d_name;
				tmp += " </a>\n";
                std::cout << "NAME : " <<ent->d_name << std::endl;
            }
        }
        closedir(dir);
        tmp += "</pre><hr></body>";
		tmp += "</html>";
    }
    std::cout << tmp << std::endl;
    index_str = tmp;
    return index_str;
}

std::string Autodex::getIndexStr()
{
    return index_str;
}

/*
<p>You can reach Michael at:</p>

<ul>
  <li><a href="https://example.com">Website</a></li>
  <li><a href="mailto:m.bluth@example.com">Email</a></li>
  <li><a href="tel:+123456789">Phone</a></li>
</ul>
*/