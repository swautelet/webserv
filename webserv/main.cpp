/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:20:16 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/20 17:17:24 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.hpp"


int main(int argc, char **argv)
{
    Response res;
    Request req;
    Conf conf;

    if(argc != 2)
        printerr("Usage : ./Webserv [conf file]");
    conf.parsing(argv[1]);
    int backlog = 10;
    int connection;
    Socket sock("9999", "127.0.0.1");
    
    sock.create_socket();
    sock.create_bind();
    sock.listen_socket(backlog);
    struct sockaddr client_address;
    size_t addrlen = sizeof((socklen_t *)&client_address);
    std::string hello;
    std::cout << "\n+++++++ Waiting for new connection ++++++++\n\n" << std::endl;
    if ((connection = accept(sock.getFd(), (struct sockaddr*)&client_address, (socklen_t*)&addrlen)) < 0)
        return printerr("cannot connect ...");
    req.getInfo(connection);
    res.find_method(req);
    res.concat_response();

    write(connection, res.getResponse().c_str(), atoi(res.getContentLenght().c_str()));
    close(connection);
    close(sock.getFd());
}