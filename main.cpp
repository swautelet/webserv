/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:20:16 by shyrno            #+#    #+#             */
/*   Updated: 2022/10/18 17:15:36 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.hpp"

fd_set sstock, sready, rstock, rready;
int g_ctrl_called = 0;
int max_fd;
std::vector<std::string> ip_vec;

int select_connection(int connection)
{
    struct timeval tv;
    int status = 0;

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    fd_set tset, tstock, wset, wstock;
    FD_ZERO(&tstock);
    FD_ZERO(&wstock);
    FD_SET(connection, &tstock);
    FD_SET(connection, &wstock);
    while (!g_ctrl_called && status == 0)
    {
        FD_ZERO(&tset);
        FD_ZERO(&wset);
        tset = tstock;
        wset = wstock;
        usleep(2000);
        std::cout << "Select connection ... " << std::endl;
        if ((status = select(connection + 1, &tset, NULL, NULL, &tv)) < 0)
        {
            if (!g_ctrl_called)
                printerr("Error with select ...");
            return (0);
        }
    }
    if (g_ctrl_called)
        return (0);
    return 1;
}

int select_connection_send(int connection)
{
    struct timeval tv;
    int status = 0;

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    fd_set tset, tstock, wset, wstock;
    FD_ZERO(&tstock);
    FD_ZERO(&wstock);
    FD_SET(connection, &tstock);
    FD_SET(connection, &wstock);
    while (!g_ctrl_called && status == 0)
    {
        FD_ZERO(&tset);
        FD_ZERO(&wset);
        tset = tstock;
        wset = wstock;
        usleep(2000);
        std::cout << "Select connection ... " << std::endl;
        if ((status = select(connection + 1, NULL, &wset, NULL, &tv)) < 0)
        {
            if (!g_ctrl_called)
                printerr("Error with select ...");
            return (0);
        }
    }
    if (g_ctrl_called)
        return (0);
    return 1;
}


void setup(webServ & web, int backlog)
{
    FD_ZERO(&sready);
    FD_ZERO(&rready);
    for (unsigned long i = 0; i < web.getConf().getNbrServer(); i++)
    {
        int no = 0;
        std::string tmp = web.getConf().getConflist(i).getAdress() + ":" + web.getConf().getConflist(i).getPort();
        for(std::vector<std::string>::iterator it = ip_vec.begin(); it != ip_vec.end(); it++)
            if (!it->compare(tmp))
                no = 1;
        if (!no)
        {
            web.getSock()[i].setup(backlog, web.getConf().getConflist(i));
            FD_SET(web.getSock()[i].getFd(), &sstock);
            FD_SET(web.getSock()[i].getFd(), &rstock);
            ip_vec.push_back(web.getConf().getConflist(i).getAdress() + ":" + web.getConf().getConflist(i).getPort());
            if (web.getSock()[i].getFd() > max_fd)
                max_fd = web.getSock()[i].getFd();
        }
    }
    for(std::vector<std::string>::iterator it = ip_vec.begin(); it != ip_vec.end(); it++)
        std::cout << "Unique ip:" << *it << std::endl;
}

void error_handling(webServ & web)
{
    int j;
    if (!web.getConf().getNbrServer())
        printerr("Error : No server configured ...");
    for (unsigned long i = 0; i < web.getConf().getNbrServer(); i++)
    {
        j = -1;
        if (web.getConf().getAddress(i).empty() || web.getConf().getPort(i).empty())
            printerr("Error : No address or port configured ...");
        else
        {
            std::string check_address = web.getConf().getAddress(i);
            std::string check_port = web.getConf().getPort(i);
            // while (check_address[++j])
            //     if (!isdigit(check_address[j]) && check_address[j] != '.')
            //         printerr("Error : Address must be numeric ...");
            // j = -1;
            while(check_port[++j])
                if (!isdigit(check_port[j]))
                    printerr("Error : Port must be numeric ...");
        }
        if (web.getConf().getServName(i).empty())
            web.getConf().getConflist(i).setServName("My Default Server");
        if (!web.getConf().getPath(i).compare("../"))
        {
            //std::cout << web.getConf().getServName(i) << std::endl;
            web.getConf().getConflist(i).setPath("root ./");
        }
    }
    j = -1;
}

int routine(webServ &web, std::string str, char *buffer, int connection, int ret, int i)
{
    if (!str.empty())
    {
        web.getReq().getInfo(connection, str);
        std::string tmp = buffer;
        int sizeheader = tmp.find("\r\n\r\n") + 4;
        if (web.getReq().getBrutbody_fileno() != -1)
            web.getReq().Write_Brutbody(buffer + sizeheader, ret - sizeheader);
        else
            printerr("error with brutbody");
        while (!g_ctrl_called && web.getReq().getWrote() < atoi(web.getReq().getContentLength().data()) && web.getReq().getWrote() >= 0)
        {
            if (!select_connection(connection))
                 return 0;
            if ((ret = recv(connection, buffer, BUFFER_SIZE - 1, 0)) > 0)
            {
                if (web.getReq().getBrutbody_fileno() != -1)
                    web.getReq().Write_Brutbody(buffer, ret);
            }
            else
                printerr("Recv body -1 ...");
        }
        web.getRes().find_method(web, i);
        web.getRes().concat_response(web);
		if (select_connection_send(connection))
        	send(connection, web.getRes().getResponse().c_str(), web.getRes().getResponse().size(), 0);
        web.getCgi().setCGIBool(0);
        str = "";
        if (web.getReq().getBrutbody_fileno() != -1)
            fclose(web.getReq().getBrutBody());
    }
    return 1;
}

int engine(webServ & web)
{
    char buffer[BUFFER_SIZE];
    std::string str = "";
    int ret;
    int i = 0;

    for(std::vector<Socket>::iterator it = web.getSock().begin(); it != web.getSock().end();it++)
        if (FD_ISSET(it->getFd(), &sstock))
            std::cout << "fd on stock are : " << it->getFd() << std::endl;
    std::cout << std::endl;
    for(std::vector<Socket>::iterator it = web.getSock().begin(); it != web.getSock().end();it++)
    {
        if (FD_ISSET(it->getFd(), &sready))
        {
            int connection = -1;
            memset(buffer, 0, BUFFER_SIZE);
            struct sockaddr client_address;
	        int addrlen = sizeof(sizeof(struct sockaddr_in));
            //std::cout << "Accept ... " << std::endl;
            if ((connection = accept(it->getFd(), (struct sockaddr*)&client_address, (socklen_t*)&addrlen)) < 0)
            {
                printerr("Error with accept ...");
                return (0);
            }
            if ((fcntl(connection, F_SETFL, O_NONBLOCK)) < 0)
            {
                printerr("Error with fcntl ...");
                return (0);
            }
            if (!select_connection(connection))
                return 0;
            std::cout << "This if fd before accept : " << it->getFd() << std::endl;
            //std::cout << "fd of connection after accept : " << connection << std::endl;
            //std::cout << "errno : " << errno << std::endl;
            if ((ret = recv(connection, buffer, sizeof(buffer) - 1, 0)) > 0)
            {
                buffer[ret] = '\0';
                str += buffer;
                if (!routine(web, str, buffer, connection, ret, i))
                {
                    close(connection);
                    printerr("Error with routine ...");
                    return 0;
                }
            }
            else
            {
                std::cout << strerror(errno) << std::endl;
                close(connection);
                std::cout << "NO ONE ELSE, ret : " << ret <<std::endl;
                printerr("Recv -1 ...");
            }
            close(connection);
        }
        i++;
    }
    return 1;
}

void ctrl_c(int sig)
{
	(void)sig;
    g_ctrl_called = 1;
    std::cout << "\nBye bye" << std::endl;
}

int loopselect()
{
    int status = 0;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    while(!g_ctrl_called && status == 0)
    {
        FD_ZERO(&sready);
        FD_ZERO(&rready);
        sready = sstock;
        rready = rstock;
        usleep(20);
        if ((status = select(max_fd + 1, &sready, &rready, NULL, &tv)) < 0)
        {
            if (!g_ctrl_called)
                printerr("Error with select ...");
            return (0);
        }
    }
    if (g_ctrl_called)
        return 0;
    return 1;
}

int main(int argc, char **argv, char **envp)
{
    FD_ZERO(&sstock);
    FD_ZERO(&sready);
    if (argc != 2)
        printerr("Usage : ./Webserv [conf file]");
    webServ web(argv[1], envp);
	web.setServ_Root(envp);
    web.getCgi().set_transla_path(envp);
    setup(web, 0);
    error_handling(web);
    std::cout << "\n+++++++ Waiting for new connection ++++++++\n\n" << std::endl;
    signal(SIGINT, &ctrl_c);
    while(!g_ctrl_called)
        if (!loopselect() || (!engine(web)))
            break;
    web.cleave_info();
}
