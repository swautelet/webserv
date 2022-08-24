/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confData.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 05:45:59 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/18 18:52:04 by chly-huc         ###   ########.fr       */
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
        int parsing(std::string path);
        int getLocationNbr() const;
        int getAutoIndex() const;
        location& LocationFinder(std::string str) const;
        const std::string& getAdress() const;
        std::string getPort() const;
        std::string getPath() const;
        std::string getServName() const;
        std::string getMethod() const;
        std::vector<std::string> getIndex() const;
        std::string getErrorPage() const;
        std::string getBodySize() const;
        location & getLocation(int index) const;
        location & getGoodLocation(std::string str) const;
        void print_info();
        void scrapData();
        void setAddress(std::string str);
        void setPath(std::string str);
        void setServName(std::string str);
        void setMethod(std::string str);
        void setIndex(std::string str);
        void setErrorPage(std::string str);
        void setBodySize(std::string str);
        void setAutoIndex(std::string str);
    private:
        std::string address;
        std::string port;
        std::string path;
        std::string serv_name;
        std::string method;
        std::vector<std::string> index;
        std::string error_page;
        std::string body_size;
        int autoindex;
        int nbr_loc;
        std::vector<location> *loc;
};

#endif
