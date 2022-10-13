/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonwautelet <simonwautelet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:42:04 by shyrno            #+#    #+#             */
/*   Updated: 2022/10/13 19:44:16 by simonwautel      ###   ########.fr       */
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
        void clear_info();
        void concat_response(webServ & serv);
        void find_method(webServ & web, int i);
        void MethodDel(webServ& web, confData& conf);
        void MethodPost(webServ & web, confData & conf);
        void MethodGet(webServ & web, confData & conf);
        
        void  setStatMsg();
		void  seterrorpage();
		void  setContentType();
		void  setContentLength();
    	void  setStatus(int status);
		void  setBody(std::string str);
    	int   setContentType(std::string str);
        void  set_FullResponse(std::string str);
        
		int getStatus() const;
        size_t getBodySize() const;
        std::string getBody() const;
		std::string getVersion() const;
        std::string getResponse() const;
        std::string getContentType() const;
        std::string getFullResponse() const;
        std::string getContentLength() const;
    private:
        std::string version;
        int status;
        std::string stat_msg;
        std::string content_type;
        std::string content_length;
        std::string body;
        std::string full_response;
};

#endif

