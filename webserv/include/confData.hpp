/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confData.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 05:45:59 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/08 01:48:05 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFDATA_HPP
#define CONFDATA_HPP

#include "header.hpp"

class location;

class confData
{
    public:
        confData();
        ~confData();
        confData(const confData & other);
        int parsing(char *path);
        int getLocationNbr();
        std::string getAdress();
        std::string getPort();
        std::string getPath();
        std::string getServName();
        std::string getMethod();
        std::string getIndex();
        std::string getErrorPage();
        location & getLocation(int index);
        void print_info();
        void scrapData();
        void setAddress(std::string str);
        void setPath(std::string str);
        void setServName(std::string str);
        void setMethod(std::string str);
        void setIndex(std::string str);
        void setErrorPage(std::string str);
    private:
        std::string address;
        std::string port;
        std::string path;
        std::string serv_name;
        std::string method;
        std::string index;
        std::string error_page;
        int autoindex;
        int nbr_loc;
        std::vector<location> *loc;
};

#endif