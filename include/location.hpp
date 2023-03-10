/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:02:39 by chly-huc          #+#    #+#             */
/*   Updated: 2022/09/27 19:16:15 by chly-huc         ###   ########.fr       */
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
        void print_info() const;
        int scrapData(std::string str);
        void edit_info(std::string str, std::string info, std::vector<std::string> vec);
        int getAutoIndex() const;
        int getCGI() const;
        std::string getPath() const;
        std::string getMethod() const;
        std::string getBodySize() const;
        std::string getErrorPage() const;
        std::string getLocation_name() const;
        std::string getCGIPath() const;
        std::vector<std::string> getIndex() const;
        const std::vector<std::string> & getRedir() const;
        
        void setPath(std::string str);
        void setIndex(std::string str);
        void setRedir(std::string str);
        void setMethod(std::string str);
        void setBodySize(std::string str);
        void setAutoIndex(std::string str);
        void setErrorPage(std::string str);
        void setCGI(std::string str);
        void setCGIPath(std::string str);
        void setLocation_name(std::string& str);
    private:
        std::string path;
        std::string method;
        std::string error_page;
        std::vector<std::string> index;
        std::string location_name;
        std::string body_size;
        std::string cgi_upload_path;
        int autoindex;
        int cgi;
        std::vector<std::string> redir;
};


#endif

