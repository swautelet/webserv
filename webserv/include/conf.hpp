/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 05:49:12 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/18 18:51:40 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_HPP
#define CONF_HPP

#include "header.hpp"
#include <vector>

class confData;

class Conf
{
    public:
        Conf();
        ~Conf();
        Conf(const Conf & other);
        std::string getAddress(int index);
        std::string getPort(int index);
        std::string getPath(int index);
        std::string getServName(int index);
        std::string getMethod(int index);
        std::vector<std::string> getIndex(int index);
        confData & getConflist(int index);
        int getNbrServer();
        void parsing(std::string path);
        void print_info();
    private:
        std::vector<confData> *confList;
        int nbr_serv;
};

#endif
