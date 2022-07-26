/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:20:16 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/24 19:29:22 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.hpp"

// int main(void)
// {
//     fd_set rfds;
//     struct timeval tv;
//     int retval;

//     /* Surveiller stdin (fd 0) en attente d'entrées */
//     //FD_ZERO(&rfds);
//     FD_SET(0, &rfds);

//     /* Pendant 5 secondes maxi */
//     tv.tv_sec = 5;
//     tv.tv_usec = 0;

//     retval = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
//     /* Considérer tv comme indéfini maintenant ! */

//     if (retval == -1)
//         perror("select()");
//     else if (retval)
//         printf("Des données sont disponibles maintenant\n");
//         /* FD_ISSET(0, &rfds) est vrai */
//     else
//         printf("Aucune données durant les 5 secondes\n");

//     exit(EXIT_SUCCESS);
// }

int main(int argc, char **argv)
{
    int i;
    Conf conf;
    Request req;
    Response res;
    int connection;
    int addrlen;
    int backlog = 10;
    fd_set fdset, copyset;
    std::vector<Socket> *sock;
    struct sockaddr client_address;
    struct timeval tv;

    
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
    addrlen = sizeof((socklen_t *)&client_address);
    memcpy(&copyset, &fdset, sizeof(fdset));
    while(1)
    {
        int retval = select(FD_SETSIZE, &copyset, NULL, NULL, &tv);
        if (retval == -1)
            printerr("Error with select ...");
        else if (retval)
        {
            for(int i = 0; i <= conf.getNbrServer(); i++)
            {
                if (FD_ISSET((*sock)[i].getFd(), &fdset))
                {
                    if ((connection = accept((*sock)[i].getFd(), (struct sockaddr*)&client_address, (socklen_t*)&addrlen)) < 0)
                      return printerr("cannot connect ...");
                    req.getInfo(connection);
                    res.find_method(req, conf.getConflist(i));
                    res.concat_response();      
                    write(connection, res.getResponse().c_str(), atoi(res.getContentLenght().c_str()));
                    close(connection);
                    return 1;
                }
            }
            
        }
    }
}
