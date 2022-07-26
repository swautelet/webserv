/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:45:19 by chly-huc          #+#    #+#             */
/*   Updated: 2022/07/26 19:12:36 by chly-huc         ###   ########.fr       */
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
    std::ofstream out;

    out.open(path, std::ofstream::trunc);
    if (out.is_open())
        std::cout << "index open ..." << std::endl;
    std::string tmp;

    std::string full_path;
    tmp = "<p>Index of " + path + "</p>\n\n<ul>\n<li><a href=\"" + full_path + "\"" + ">X</a><li>\n" + "</ul>";
    out << tmp;
}



/*
<p>You can reach Michael at:</p>

<ul>
  <li><a href="https://example.com">Website</a></li>
  <li><a href="mailto:m.bluth@example.com">Email</a></li>
  <li><a href="tel:+123456789">Phone</a></li>
</ul>
*/