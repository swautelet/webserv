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

class webServ
{
    public:
        webServ();
        ~webServ();
        webServ(std::string argv);
        webServ(const webServ & other);
        webServ &operator=(webServ const & other);
        Conf &getConf();
        Request & getReq();
        Response & getRes();
        std::vector<Socket> &getSock();
        Autodex & getAutodex();
    private:
        Conf conf;
        Request req;
        Response res;
        std::vector<Socket> sock;
        Autodex indexing;
};

#endif

