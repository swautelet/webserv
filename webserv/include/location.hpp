/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:02:39 by chly-huc          #+#    #+#             */
/*   Updated: 2022/09/22 10:09:29 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "header.hpp"

class location
{
    public:
        location();
        location(const location & other);
        ~location();
		location& operator=(const location& other);
        std::string getLocation_name() const;
        std::string getMethod() const;
        std::vector<std::string> getIndex() const;
        std::string getPath() const;
        std::string getErrorPage() const;
        std::string getBodySize() const;
        int getAutoIndex() const;
        const std::vector<std::string> & getRedir() const;
        void setLocation_name(std::string& str);
        void setBodySize(std::string str);
        void setPath(std::string str);
        void setMethod(std::string str);
        void setIndex(std::string str);
        void setAutoIndex(std::string str);
        void setErrorPage(std::string str);
        void setRedir(std::string str);
        int scrapData(std::string str, int i);
        void print_info() const;
        void edit_info(std::string str, std::string info, std::vector<std::string> vec);
    private:
        std::string path;
        std::string method;
        std::string error_page;
        std::vector<std::string> index;
        std::string location_name;
        std::string body_size;
        int autoindex;
        std::vector<std::string> redir;
};


#endif
