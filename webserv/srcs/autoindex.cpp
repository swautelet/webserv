/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:45:19 by chly-huc          #+#    #+#             */
/*   Updated: 2022/08/18 20:14:53 by chly-huc         ###   ########.fr       */
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

std::string Autodex::create_dex(webServ & web, confData & conf)
{
    DIR *dir;
    struct dirent *ent;
    struct stat info;
    std::ofstream out;
    std::string full_path;
    std::string path;
    std::string tmp;
    int i = -1;
    int autodex = 0;

    std::cout << "--------------AUTOINDEX CREATION---------------" << std::endl;
    path = web.getReq().getUrl();

    std::cout << "FULL_PATH == " << full_path << std::endl;
    std::cout << "PATH == " << path << std::endl;
    if (stat(path.c_str(), &info) != 0)
        std::cout << "AH\n";
    while(++i < conf.getLocationNbr())
    {
        if (!conf.getLocation(i).getLocation_name().compare(path))
        {
            std::cout << "---- " << conf.getLocation(i).getLocation_name() << std::endl;
            std::cout << "---- " << conf.getLocation(i).getAutoIndex() << std::endl;
            autodex = conf.getLocation(i).getAutoIndex();
            full_path = path + "/" + conf.getLocation(i).getIndex()[0];
            path = conf.getGoodLocation(path).getPath();
            break;
        }
    }

    full_path = "www/index/index.html";
    if (autodex)
        out.open(full_path, std::ofstream::trunc);
    else
        out.open(path, std::ofstream::trunc);
    if (out.is_open())
        std::cout << "index open ..." << std::endl;
    if ((dir = opendir(path.c_str())) != NULL)
    {
        tmp += "<p>Index of " + path + "</p>\n\n<ul>\n";
        while ((ent = readdir(dir)) != NULL)
        {
            if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))
            {
                tmp += "<li><a href=\"";
                tmp += path + "/" + ent->d_name + "\"" + ">" + ent->d_name + "</a><li>\n";
                std::cout << "NAME : " <<ent->d_name << std::endl;
            }
        }
        tmp += "</ul>";
    }
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