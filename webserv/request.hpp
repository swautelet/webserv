/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:02:47 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/01 03:42:33 by shyrno           ###   ########.fr       */
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
        void getInfo(int connection);
        std::string getUrl();
        std::string getMethod();
        std::string getVersion();
        std::string getHeader();
        std::string getBody();
    private:
        std::string method;
        std::string url;
        std::string version;
        std::string header;
        std::string body;
};

#endif