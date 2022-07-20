/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:31:43 by shyrno            #+#    #+#             */
/*   Updated: 2022/06/28 03:01:09 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "header.hpp"

class Socket
{
    public:
        Socket();
        Socket(std::string port, std::string ip);
        Socket(const Socket & other);
        Socket &operator=(const Socket & other);
        void set_ip(std::string ip);
        void set_port(std::string port);
        int create_socket();
        int create_bind();
        int listen_socket(int max_queue);
        sockaddr_in getServ_address();
        std::string getIp();
        std::string getPort();
        int getFd();
        ~Socket();
    private:
        sockaddr_in serv_address;
        int fd;
        std::string ip;
        std::string port;
};

#endif