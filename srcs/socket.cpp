/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:33:26 by shyrno            #+#    #+#             */
/*   Updated: 2022/10/11 01:40:36 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"


Socket::Socket()
{
    fd = -1;
    std::cout << "Socket constructor" << std::endl;
}

Socket::~Socket()
{
    std::cout << "Destructor socket called : " << fd <<std::endl;
}

Socket::Socket(std::string ip, std::string port)
{
    fd = -1;
	std::cout << "socket second constructor called " << std::endl;
    this->ip = ip;
    this->port = port;
}

Socket::Socket(const Socket & other)
{
    this->serv_address = other.serv_address;
    this->fd = other.fd;
    this->ip = other.ip;
    this->port = other.port;
    //fd = -1;
    std::cout << fd << std::endl;
}

void Socket::setup(int backlog, confData & conf)
{
    create_socket(conf);
    create_bind();
    listen_socket(backlog);
    set_ip(conf.getAdress());
    set_port(conf.getPort());
}

int Socket::create_socket(confData & conf)
{
    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_address.sin_port = htons(atoi(conf.getPort().data()));
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
    if ((fcntl(fd, F_SETFL, O_NONBLOCK)) < 0)
        return printerr("Error with fcntl ...");
    return 1;
}

void Socket::set_ip(const std::string& ip)
{
    this->ip = ip;
}

void Socket::set_port(std::string port)
{
    this->port = port;
}

void Socket::set_fd(int fd)
{
    this->fd = fd;
}

sockaddr_in Socket::getServ_address() const
{
    return serv_address;
}

std::string Socket::getIp() const
{
    return ip;
}

std::string Socket::getPort() const
{
    return port;
}

const int& Socket::getFd() const
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

void Socket::close_fd()
{
    close(fd);
}