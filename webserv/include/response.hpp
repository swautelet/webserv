/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:42:04 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/01 00:42:46 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "header.hpp"

class Request;
class confData;
class webServ;

class Response
{
    public:
        Response();
        ~Response();
        Response(const Response & other);
        Response &operator=(const Response & other);
        void find_method(webServ & web, int i);
        void MethodGet(webServ & web, confData & conf);
        void delMethod();
        void postMethod();
        void init();
        void concat_response();
    	void  setStatus(int status);
        std::string setStatMsg();
    	void  setContentType(std::string str);
		void  setContentType();
        std::string getResponse();
        std::string getContentLenght();
        std::string getContentType();
        std::string getBody();
        std::string getFullResponse();
    private:
        std::string version;
        int status;
        std::string stat_msg;
        std::string content_type;
        std::string content_lenght;
        std::string body;
        std::string full_response;
};

#endif
