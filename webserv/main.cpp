/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:20:16 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/06 20:50:31 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.hpp"

Conf conf;
Request req;
Response res;
fd_set fdset, copyset;
std::vector<Socket> *sock;

void setup(char **argv, int backlog)
{
    int i = -1;

    conf.parsing(argv[1]);
    sock = new std::vector<Socket>(conf.getNbrServer());
    FD_ZERO(&fdset);
    while (++i < conf.getNbrServer())
    {
        (*sock)[i].setup(backlog, conf.getConflist(i));
        FD_SET((*sock)[i].getFd(), &fdset);
    }
}

void engine(int connection, int addrlen)
{
    for(int i = 0; i <= conf.getNbrServer(); i++)
    {
        if (FD_ISSET((*sock)[i].getFd(), &fdset))
        {
            struct sockaddr client_address;
            addrlen = sizeof((socklen_t *)&client_address);
            std::cout << "Accept ... " << std::endl; 
            if ((connection = accept((*sock)[i].getFd(), (struct sockaddr*)&client_address, (socklen_t*)&addrlen)) < 0)
                printerr("cannot connect ...");
            std::cout << "Accept done ..." << std::endl;
            req.getInfo(connection);
            //Autodex index(req.getUrl(), conf.getConflist(0));
            res.find_method(req, conf.getConflist(i));
            res.concat_response();      
            write(connection, res.getResponse().c_str(), res.getResponse().size());
            close(connection);
            break;
        }
    }
}

int main(int argc, char **argv)
{
    struct timeval tv;
    int i = -1;
    int connection = 0;
    int addrlen = 0;
    int backlog = 10;
    int retval = 0;
    tv.tv_sec = 60;
    tv.tv_usec = 0;
    if (argc != 2)
        printerr("Usage : ./Webserv [conf file]");
    setup(argv, backlog);
    std::cout << "\n+++++++ Waiting for new connection ++++++++\n\n" << std::endl;
    memcpy(&copyset, &fdset, sizeof(fdset));
    while(1)
    {
        if ((retval = select(FD_SETSIZE, &copyset, NULL, NULL, &tv)) == -1)
            printerr("Error with select ...");
        else if (retval)
            engine(connection, addrlen);
    }
}


