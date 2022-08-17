/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:45:15 by chly-huc          #+#    #+#             */
/*   Updated: 2022/08/17 17:05:05 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOINDEX_HPP
#define AUTOINDEX_HPP

#include "../include/header.hpp"

class Autodex
{
    public:
        Autodex();
        ~Autodex();
        Autodex(const Autodex & other);
        Autodex(std::string path, confData & conf);
        std::string getIndexStr();
    private:
        std::string index_str;
};

#endif