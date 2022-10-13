/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonwautelet <simonwautelet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:02:47 by shyrno            #+#    #+#             */
/*   Updated: 2022/10/13 19:15:28 by simonwautel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "header.hpp"

class Request
{
    public:
        Request();
        ~Request();
        void clear_info();
        Request(const Request & other);
		Request& operator=(const Request& other);
        void _search_info(std::vector<std::string> req, std::string buff);

        int getInfo(int connection, std::string string);
        std::string getUrl() const;
        std::string getContentType() const;
        std::string getBody() const;
        std::string getMethod() const;
        std::string getHeader() const;
        std::string getVersion() const;
        std::string getContentLength() const;
        int    getWrote() const;
        void        add_Wrote(int read);
        void        Write_Brutbody(char* buff, int size);
		const std::vector<std::string>& getDataType() const;
        std::string getQuery_string();
        int getBrutbody_fileno();
        void    clean_header();
        
    private:
        FILE* brutbody;
        std::string method;
        std::string url;
        std::string version;
        std::string header;
        std::string body;
        std::string content_length;
		std::vector<std::string> type_data;
        std::string query_s;
        std::string content_type;
        long int wrote;
};

#endif

