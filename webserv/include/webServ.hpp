/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:10:21 by shyrno            #+#    #+#             */
/*   Updated: 2022/09/14 18:41:13 by chly-huc         ###   ########.fr       */
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
        webServ(std::string argv);
        webServ(webServ & other);
        webServ &operator=(webServ const & other);
        Conf &getConf();
        Request & getReq();
        Response & getRes();
		Cgi&	getCgi();
        std::vector<Socket> &getSock();
        Autodex & getAutodex();
        std::pair<std::string, std::string> &getbool_redir();
		void	setServ_Root(char **env);
        void setbool_redir(std::vector<std::string> vec);
        void del_redir();
		const std::string&	getServ_Root() const;
		char** env;
    private:
        Conf* conf;
        Request* req;
        Response* res;
        std::vector<Socket> sock;
        Autodex* indexing;
		std::string	serv_root;
        std::pair<std::string, std::string> bool_redir;
		Cgi* _cgi;
};

#endif

