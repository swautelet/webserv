/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:02:47 by shyrno            #+#    #+#             */
/*   Updated: 2022/09/26 18:34:01 by chly-huc         ###   ########.fr       */
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
        Request(const Request & other);
		Request& operator=(const Request& other);
        void getInfo(int connection);
        std::string getUrl() const;
        std::string getMethod() const;
        std::string getVersion() const;
        std::string getHeader() const;
        std::string getBody() const;
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
};

#endif
