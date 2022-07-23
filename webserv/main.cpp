/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:20:16 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/23 21:54:00 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.hpp"


int main(int argc, char **argv)
{
    int i;
    Conf conf;
    Request req;
    Response res;
    int connection;
    int addrlen;
    int backlog = 10;
    fd_set fdset;
    std::vector<Socket> *sock;
    struct sockaddr client_address;

    i = -1;
    if (argc != 2)
        printerr("Usage : ./Webserv [conf file]");
    conf.parsing(argv[1]);
    sock = new std::vector<Socket>(conf.getNbrServer());
    while (++i < conf.getNbrServer())
    {
        (*sock)[i].setup(backlog, conf.getConflist(i));
        FD_SET((*sock)[i].getFd(), &fdset);
    }
    std::cout << "\n+++++++ Waiting for new connection ++++++++\n\n" << std::endl;

    i = -1;
    while(++i < conf.getNbrServer())
    {
        addrlen = sizeof((socklen_t *)&client_address);
        if ((connection = accept((*sock)[i].getFd(), (struct sockaddr*)&client_address, (socklen_t*)&addrlen)) < 0)
            return printerr("cannot connect ...");
        std::cout << "--------" << std::endl;
        req.getInfo(connection);
        res.find_method(req);
        res.concat_response();      
        write(connection, res.getResponse().c_str(), atoi(res.getContentLenght().c_str()));
        close(connection);
    }
}