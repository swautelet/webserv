/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:45:19 by chly-huc          #+#    #+#             */
/*   Updated: 2022/09/26 15:22:32 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autoindex.hpp"

Autodex::Autodex()
{
    std::cout << "Autoindex constructor " << std::endl;
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
    
    struct dirent *ent;
    std::ofstream out;
    std::string path;
    std::string tmp;
    std::string full_url(url);
    std::string loca = loc.getPath().substr(2, loc.getPath().size());
    int i = -1;
//    int autodex = 0;

    std::cout << "autoindex" << std::endl;
    std::cout << "--------------AUTOINDEX CREATION---------------" << std::endl;
    print(url);
    print(conf.getPath());
    if (web.getReq().getUrl().size() > 1)
        path = conf.getPath();
    else
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
            std::cout << "---- " << conf.getLocation(i).getLocation_name() << std::endl;
            std::cout << "---- " << conf.getLocation(i).getAutoIndex() << std::endl;
           /* autodex = */conf.getLocation(i).getAutoIndex();
            path = conf.getGoodLocation(path).getPath();
            web.setMax_body_size(atoi(conf.getLocation(i).getBodySize().c_str()));
            break;
        }
    }
    if ((dir = opendir(url.c_str())) != NULL)
    {
		std::cout << "i begin to write autoindex " << std::endl;
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
                        // std::cout << "Hyperlink " << path + "/" + ent->d_name << std::endl;
                        tmp += ent->d_name;
                        tmp += ">";
                        tmp += ent->d_name;
                        tmp += " </a>\n";
                    }
                    // std::cout << "NAME : " <<ent->d_name << std::endl;
            }
        }
        closedir(dir);
        tmp += "</pre><hr></body>\n";
		tmp += "</html>";
    }
    index_str = tmp;
    web.getRes().setContentType(".html");
    return index_str;
}

std::string Autodex::getIndexStr() const
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
