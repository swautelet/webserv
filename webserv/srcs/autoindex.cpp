/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:45:19 by chly-huc          #+#    #+#             */
/*   Updated: 2022/08/17 17:05:48 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/autoindex.hpp"

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

Autodex::Autodex(std::string path, confData & conf)
{
    (void)conf;
    (void)path;
    DIR *dir;
    struct dirent *ent;
    struct stat info;
    std::ofstream out;
    std::string full_path;
    std::string tmp;
    int i = -1;
    int autodex = 0;

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
            if (!conf.getPath().compare("./www/index"))
                path = conf.getPath();
            else
                path = conf.getPath() + "/" + "index"; 
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
}

std::string Autodex::getIndex()
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