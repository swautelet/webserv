/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confData.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 05:45:59 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/12 07:23:06 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFDTATA_HPP
#define CONFDATA_HPP

#include "header.hpp"

class confData
{
    public:
        confData();
        ~confData();
        confData(const confData & other);
        void parsing(char *path);
        std::string getAdress();
        std::string getPort();
        std::string getPath();
        std::string getServName();
        std::string getMethod();
        std::string getIndex();
        void setAddress(char *str);
        void setPath(char *str);
        void setServName(char *str);
        void setMethod(char *str);
        void setIndex(char *str);
    private:
        std::string address;
        std::string port;
        std::string path;
        std::string serv_name;
        std::string method;
        std::string index;
        int autoindex;
};


#endif