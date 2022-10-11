/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:31:43 by shyrno            #+#    #+#             */
/*   Updated: 2022/10/11 01:47:46 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "header.hpp"

class confData;

class Socket
{
    public:
        Socket();
        ~Socket();
        Socket(std::string port, std::string ip);
        Socket(const Socket & other);
        Socket &operator=(const Socket & other);
        int create_bind();
        int listen_socket(int max_queue);
        int create_socket(confData & conf);
        void setup(int backlog, confData & conf);
        
        void set_port(std::string port);
        void set_ip(const std::string& ip);
        
        const int& getFd() const;
        std::string getIp() const;
        std::string getPort() const;
        sockaddr_in getServ_address() const;
        sockaddr_in serv_address;
    private:
        int fd;
        std::string ip;
        std::string port;
};

#endif

