/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:45:15 by chly-huc          #+#    #+#             */
/*   Updated: 2022/09/27 19:16:05 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOINDEX_HPP
#define AUTOINDEX_HPP

#include "header.hpp"
#include <dirent.h>
class webServ;

class Autodex
{
    public:
        Autodex();
        ~Autodex();
        Autodex(const Autodex & other);
        std::string getIndexStr() const;
		Autodex& operator=(const Autodex& other);
        Autodex(std::string path, confData & conf);
        std::string create_dex(webServ & web, std::string url);
        std::string html_creation(DIR *dir, std::string url);
    private:
        std::string index_str;
};

#endif

