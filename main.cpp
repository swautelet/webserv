/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonwautelet <simonwautelet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:20:16 by shyrno            #+#    #+#             */
/*   Updated: 2022/10/13 19:50:20 by simonwautel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.hpp"


fd_set fdset, copyset;
int g_ctrl_called = 0;

void fd_update()
{
    FD_ZERO(&copyset);
    copyset = fdset;
}

void setup(webServ & web, int backlog)
{
    std::vector<std::string> ip_vec;
    for (unsigned long i = 0; i < web.getConf().getNbrServer(); i++)
    {
        int no = 0;
        std::string tmp = web.getConf().getConflist(i).getAdress() + ":" + web.getConf().getConflist(i).getPort() + " " + web.getConf().getConflist(i).getServName();
        tmp = tmp.substr(0, tmp.find(" "));
        for(std::vector<std::string>::iterator it = ip_vec.begin(); it != ip_vec.end(); it++)
            if (!it->substr(0, it->find(" ")).compare(tmp))
                no = 1;
        if (!no)
        {
            web.getSock()[i].setup(backlog, web.getConf().getConflist(i));
            FD_SET(web.getSock()[i].getFd(), &fdset);
            ip_vec.push_back(web.getConf().getConflist(i).getAdress() + ":" + web.getConf().getConflist(i).getPort() + " " + web.getConf().getConflist(i).getServName());  
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
            std::cout << web.getConf().getServName(i) << std::endl;
            web.getConf().getConflist(i).setPath("root ./");
        }
    }
    j = -1;
}

void routine(webServ &web, std::string str, char *buffer, int connection, int ret, int i)
{
    if (!str.empty())
    {
        web.getReq().getInfo(connection, str);
        std::string tmp = buffer;
        int sizeheader = tmp.find("\r\n\r\n") + 4;
        web.getReq().Write_Brutbody(buffer + sizeheader, ret - sizeheader);
        while (web.getReq().getWrote() < atoi(web.getReq().getContentLength().data()) && web.getReq().getWrote() >= 0)
        {
            select_connection(connection);
            ret = recv(connection, buffer, sizeof(buffer) - 1, 0);
            web.getReq().Write_Brutbody(buffer, ret);
        }
        web.getRes().find_method(web, i);
        web.getRes().concat_response(web);
        write(connection, web.getRes().getResponse().c_str(), web.getRes().getResponse().size());
        web.getCgi().setCGIBool(0);
        str = "";
    }
}
void engine(webServ & web, int connection, int addrlen)
{
    char buffer[100001];
    std::string str;
    for(unsigned long i = 0; i < web.getConf().getNbrServer(); i++)
    {
        if (FD_ISSET(web.getSock()[i].getFd(), &copyset))
        {
            memset(buffer, 0, 100000);
            addrlen = sizeof(web.getSock()[i].serv_address);
            std::cout << "Accept ... " << std::endl;
            if ((connection = accept(web.getSock()[i].getFd(), (struct sockaddr*)&web.getSock()[i].serv_address, (socklen_t*)&addrlen)) < 0)
                printerr("cannot connect ...");
            if ((fcntl(connection, F_SETFL, O_NONBLOCK)) < 0)
                printerr("Error with fcntl ...");
            int ret = 1;
            std::cout << "Recv ... : " << ret << std::endl;
            select_connection(connection);
            if ((ret = recv(connection, buffer, sizeof(buffer) - 1, 0)) > 0)
            {
                buffer[ret] = '\0';
                str += buffer;
            }
            routine(web, str, buffer, connection, ret, i);
            close(connection);
            return ;
        }
        
    }
}

void ctrl_c(int sig)
{
	(void)sig;
    g_ctrl_called = 1;
    std::cout << "\nBye bye" << std::endl;
    exit(0);
}


int main(int argc, char **argv, char **envp)
{
    struct timeval tv;
    tv.tv_sec = 30;
    tv.tv_usec = 0;
    webServ web(argv[1], envp);
	web.setServ_Root(envp);
    web.getCgi().set_transla_path(envp);
    int connection = 0;
    int addrlen = 0;
    int backlog = 128;
    int retval = 0;
    if (argc != 2)
        printerr("Usage : ./Webserv [conf file]");
    setup(web, backlog);
    error_handling(web);
    std::cout << "\n+++++++ Waiting for new connection ++++++++\n\n" << std::endl;
    memcpy(&copyset, &fdset, sizeof(fdset));
    signal(SIGINT, &ctrl_c);
    while(1)
    {
        fd_update();
        if ((retval = select(FD_SETSIZE, &copyset, NULL, NULL, &tv)) == -1)
            printerr("Error with select ...");
        if (retval == 0)
            printerr("Timeout...");
        else
            engine(web, connection, addrlen);
    }
}

// payload too large 