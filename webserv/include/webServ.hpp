/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:10:21 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/18 20:02:13 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP
#include "header.hpp"
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
        char** getEnv();
        Request & getReq();
        Response & getRes();
		Cgi&	getCgi();
        std::vector<Socket> &getSock();
        Autodex & getAutodex();
		void	setServ_Root(char **env);
		const std::string&	getServ_Root() const;
        void    setEnv(char** envp);

    private:
		char** env;
        Conf* conf;
        Request* req;
        Response* res;
        std::vector<Socket> sock;
        Autodex* indexing;
		std::string	serv_root;
		Cgi* _cgi;
};

#endif

