/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:33:26 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/24 17:26:31 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"


Socket::Socket()
{
        
}

Socket::~Socket()
{
    std::cout << "Destructor socket called" << std::endl;
    close(fd);
}

Socket::Socket(std::string ip, std::string port)
{
    this->ip = ip;
    this->port = port;
}

Socket::Socket(const Socket & other)
{
    this->serv_address = other.serv_address;
    this->fd = other.fd;
    this->ip = other.ip;
    this->port = other.port;
}

void Socket::setup(int backlog, confData & conf)
{
    
    create_socket(conf);
    create_bind();
    listen_socket(backlog);
    set_ip(conf.getAdress());
    set_port(conf.getPort());
}

void Socket::set_ip(std::string ip)
{
    this->ip = ip;
}


void Socket::set_port(std::string port)
{
    this->port = port;
}

int Socket::create_socket(confData & conf)
{
    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = INADDR_ANY;
    serv_address.sin_port = htons(atoi(conf.getPort().c_str()));
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return printerr("Error with socket creation ...");
    return 1;
}

int Socket::create_bind()
{
    int yes = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (void*)&yes, sizeof(yes)) < 0)
        return printerr("Error with socket protection ...");
    if ((bind(fd,(struct sockaddr*)&serv_address, sizeof(serv_address))) < 0)
        return printerr("Error with socket binding ...");
    return 1;
}

int Socket::listen_socket(int max_queue)
{
    if (listen(fd, max_queue) < 0)
        return printerr("Error with socket listening ...");
    return 1;
}

sockaddr_in Socket::getServ_address()
{
    return serv_address;
}

std::string Socket::getIp()
{
    return ip;
}

std::string Socket::getPort()
{
    return port;
}

int Socket::getFd()
{
    return fd;
}

Socket &Socket::operator=(Socket const & other)
{
	this->serv_address = other.serv_address;
	this->fd = other.fd;
	this->port = other.port;
	this->ip = other.ip;
	return (*this);
}