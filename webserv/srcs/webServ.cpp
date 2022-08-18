/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:43:26 by chly-huc          #+#    #+#             */
/*   Updated: 2022/08/18 20:01:13 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"

webServ::webServ()
{
    
}


webServ::webServ(std::string argv)
{
    conf.parsing(argv);
    sock.reserve(conf.getNbrServer());
}

webServ::~webServ()
{
    
}

webServ::webServ(const webServ & other)
{
    
}

Conf & webServ::getConf()
{
    return conf;
}

std::vector<Socket> & webServ::getSock()
{
    return sock;
}

Request & webServ::getReq()
{
    return req;
}

Response & webServ::getRes()
{
    return res;
}

Autodex & webServ::getAutodex()
{
    return indexing;
}