/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:20:16 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/31 16:03:17 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.hpp"

int main(int argc, char **argv)
{
    int i;
    Conf conf;
    Request req;
    Response res;
    fd_set fdset, copyset;
    std::vector<Socket> *sock;
    struct timeval tv;
    int connection;
    int addrlen;
    int backlog = 10;
    i = -1;
    tv.tv_sec = 60;
    tv.tv_usec = 0;
    if (argc != 2)
        printerr("Usage : ./Webserv [conf file]");
    conf.parsing(argv[1]);
    sock = new std::vector<Socket>(conf.getNbrServer());
    FD_ZERO(&fdset);
    while (++i < conf.getNbrServer())
    {
        (*sock)[i].setup(backlog, conf.getConflist(i));
        FD_SET((*sock)[i].getFd(), &fdset);
    }
    std::cout << "\n+++++++ Waiting for new connection ++++++++\n\n" << std::endl;

    i = -1;
    memcpy(&copyset, &fdset, sizeof(fdset));
    while(1)
    {
        // FD_ZERO(&fdset);
        // for(int z = 0; z < conf.getNbrServer(); z++)
        //     FD_SET((*sock)[z].getFd(), &fdset);
        int retval = select(FD_SETSIZE, &copyset, NULL, NULL, &tv);
        if (retval == -1)
            printerr("Error with select ...");
        else if (retval)
        {
            for(int i = 0; i <= conf.getNbrServer(); i++)
            {
                if (FD_ISSET((*sock)[i].getFd(), &fdset))
                {
                    struct sockaddr client_address;
                    addrlen = sizeof((socklen_t *)&client_address);
                    std::cout << "Accept ... " << std::endl; 
                    if ((connection = accept((*sock)[i].getFd(), (struct sockaddr*)&client_address, (socklen_t*)&addrlen)) < 0)
                        return printerr("cannot connect ...");
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
    }
}


