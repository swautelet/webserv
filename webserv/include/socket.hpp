/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:31:43 by shyrno            #+#    #+#             */
/*   Updated: 2022/09/27 18:03:08 by chly-huc         ###   ########.fr       */
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
    private:
        sockaddr_in serv_address;
        int fd;
        std::string ip;
        std::string port;
};

#endif
