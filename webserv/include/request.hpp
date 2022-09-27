/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:02:47 by shyrno            #+#    #+#             */
/*   Updated: 2022/09/27 18:54:33 by chly-huc         ###   ########.fr       */
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

        int getInfo(int connection);
        std::string getUrl() const;
        std::string getBody() const;
        std::string getMethod() const;
        std::string getHeader() const;
        std::string getVersion() const;
        std::string getContentLenght() const;
		const std::vector<std::string>& getDataType() const;
        
    private:
        std::string method;
        std::string url;
        std::string version;
        std::string header;
        std::string body;
        std::string content_lenght;
		std::vector<std::string> type_data;
        std::string query_s;
};

#endif

