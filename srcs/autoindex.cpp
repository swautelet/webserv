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
}

Autodex& Autodex::operator=(const Autodex& other)
{
	index_str = other.getIndexStr();
	return *this;
}

std::string Autodex::create_dex(webServ & web, confData & conf, std::string url, const location & loc)
{
    DIR *dir;
    
    int i = -1;
    std::string path;
    std::string full_url(url);
    std::string loca = loc.getPath().substr(2, loc.getPath().size());

    // std::cout << "--------------AUTOINDEX CREATION---------------" << std::endl;
    if (web.getReq().getUrl().size() > 1)
        path = conf.getPath();
    if (path.rfind("/") == path.size() - 1)
        path = path.substr(0, path.size() - 1);
    if (url.rfind("/") == url.size() - 1)
        url = url.substr(0, url.size() - 1);
    if (url[0] == '.' && url[1] == '/')
        url.erase(0, 2);
    while(++i < conf.getLocationNbr())
    {
        if (!conf.getLocation(i).getLocation_name().compare(path))
        {
            // std::cout << "---- " << conf.getLocation(i).getLocation_name() << std::endl;
            // std::cout << "---- " << conf.getLocation(i).getAutoIndex() << std::endl;
            path = conf.getGoodLocation(path).getPath();
            char* temp = to_char(conf.getLocation(i).getBodySize());
            web.setMax_body_size(atoi(temp));
            delete[] temp;
            break;
        }
    }
    char* temp = to_char(url);
    if ((dir = opendir(temp)) != NULL)
        index_str = html_creation(dir, full_url, loca, url);
    // std::cout << "--------------AUTOINDEX ENDING---------------" << std::endl;
    delete[] temp;
    web.getRes().setContentType(".html");
    return index_str;
}

std::string Autodex::html_creation(DIR *dir, std::string full_url, std::string loca, std::string url)
{
    struct dirent *ent;
    std::string tmp;
    tmp += "<html>";
	tmp += "<head><title>Index of ";
	tmp += url + "</title></head>\n";
	tmp += "<body>\n";
	tmp += "<h1>Index of ";
	tmp += url + "</h1><hr><pre>";
    full_url = url;
    if (url.find("/") == std::string::npos)
        url = "";
    else
        url = url.substr(url.find("/"), url.size());
    while ((ent = readdir(dir)) != NULL)
    {
        if (strcmp(ent->d_name, "."))
        {
                tmp += "<a href=";
                if (!strcmp(ent->d_name, ".."))
                {
                    if (full_url.compare(loca))
                    {
                        tmp += url.substr(0, url.rfind("/"));
                        tmp += "/";
                    }
                    tmp += ">";
                    tmp += ent->d_name;
                    tmp += " </a>\n";
                }
                else
                {
                    if (!url.empty())
                    {
                        tmp += url;
                        tmp += "/";
                    }
                    tmp += ent->d_name;
                    tmp += ">";
                    tmp += ent->d_name;
                    tmp += " </a>\n";
                }
        }
    }
    closedir(dir);
    tmp += "</pre><hr></body>\n";
	tmp += "</html>";
    return tmp;
}

std::string Autodex::getIndexStr() const 
{
    return index_str;
}