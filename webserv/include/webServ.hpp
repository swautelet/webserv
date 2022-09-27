/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:10:21 by shyrno            #+#    #+#             */
/*   Updated: 2022/09/27 16:51:36 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP
#include "header.hpp"
class Response;
class Socket;
class Conf;
class Autodex;
class Cgi;

class webServ
{
    public:
        webServ();
        ~webServ();
        webServ(webServ & other);
        webServ(std::string argv);
        webServ &operator=(webServ const & other);
		Cgi & getCgi();
        Conf & getConf();
        Request & getReq();
        Response & getRes();
        Autodex & getAutodex();
        int getMax_body_size();
        std::vector<Socket> &getSock();
		const std::string&	getServ_Root() const;
        std::pair<std::string, std::string> &getbool_redir();
        void del_redir();
        void cleave_info();
        void setMax_body_size(int i);
		void setServ_Root(char **env);
        void setbool_redir(std::vector<std::string> vec);
		char** env;
    private:
		Cgi* _cgi;
        Conf* conf;
        Request* req;
        Response* res;
        Autodex* indexing;
        int max_body_size;
		std::string	serv_root;
        std::vector<Socket> sock;
        std::pair<std::string, std::string> bool_redir;
};

#endif

