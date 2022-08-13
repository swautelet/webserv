/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:02:39 by chly-huc          #+#    #+#             */
/*   Updated: 2022/08/13 20:45:29 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

class location
{
    public:
        location();
        location(const location & other);
        ~location();
        std::string getLocation_name();
        std::string getMethod();
        std::string getIndex();
        std::string getPath();
        std::string getErrorPage();
        std::string getBodySize();
        int getAutoIndex();
        void setLocation_name(std::string str);
        void setBodySize(std::string str);
        void setPath(std::string str);
        void setMethod(std::string str);
        void setIndex(std::string str);
        void setAutoIndex(std::string str);
        void setErrorPage(std::string str);
        int scrapData(char *str, int i);
        void print_info();
    private:
        std::string path;
        std::string method;
        std::string error_page;
        std::string index;
        std::string location_name;
        std::string body_size;
        int autoindex;
};


#endif