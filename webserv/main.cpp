/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:20:16 by shyrno            #+#    #+#             */
/*   Updated: 2022/09/27 19:47:51 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.hpp"

fd_set fdset, copyset;
std::vector<std::string> ip_vec;

void setup(webServ & web, int backlog)
{
    FD_ZERO(&fdset);
    for (unsigned long i = 0; i < web.getConf().getNbrServer(); i++)
    {
        int no = 0;
        for(std::vector<std::string>::iterator it = ip_vec.begin(); it != ip_vec.end(); it++)
            if (!it->compare(web.getConf().getConflist(i).getAdress() + ":" + web.getConf().getConflist(i).getPort()))
                no = 1;
        if (!no)
        {
            web.getSock()[i].setup(backlog, web.getConf().getConflist(i));
            FD_SET(web.getSock()[i].getFd(), &fdset);
            ip_vec.push_back(web.getConf().getConflist(i).getAdress() + ":" + web.getConf().getConflist(i).getPort());  
        }
    }
    for(std::vector<std::string>::iterator it = ip_vec.begin(); it != ip_vec.end(); it++)
        std::cout << "Unique ip:" << *it << std::endl;
}

void error_handling(webServ & web)
{
  ////  int i = -1;
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
            while (check_address[++j])
                if (!isdigit(check_address[j]) && check_address[j] != '.')
                    printerr("Error : Address must be numeric ...");
            j = -1;
            while(check_port[++j])
                if (!isdigit(check_port[j]))
                    printerr("Error : Port must be numeric ...");
        }
        if (web.getConf().getServName(i).empty())
            web.getConf().getConflist(i).setServName("My Default Server");
    }
    j = -1;
}

void engine(webServ & web, int connection, int addrlen)
{
    for(unsigned long i = 0; i < web.getConf().getNbrServer(); i++)
    {
        if (FD_ISSET(web.getSock()[i].getFd(), &copyset))
        {
            struct sockaddr client_address;
            addrlen = sizeof((socklen_t *)&client_address);
            std::cout << "Accept ... " << std::endl;
            if ((connection = accept(web.getSock()[i].getFd(), (struct sockaddr*)&client_address, (socklen_t*)&addrlen)) < 0)
                printerr("cannot connect ...");
            std::cout << "Accept done ..." << std::endl;
            if (web.getReq().getInfo(connection) == 0)
            {
                std::cout << "Recv connection close ... Retry ..." << std::endl;
                break;
            }
            std::cout << "Info done ..." << std::endl;
            web.getRes().find_method(web, i);
            web.getRes().concat_response(web);
            std::cout << web.getRes().getResponse().size() << " & " << web.getRes().getContentLenght().c_str() << std::endl;
            write(connection, web.getRes().getResponse().c_str(), web.getRes().getResponse().size());
            close(connection);
            memcpy(&copyset, &fdset, sizeof(fdset));
            break;
        }
        
    }
}
void ctrl_c(int sig)
{
	(void)sig;
	(void)sig;
    std::cout << "\nBye bye" << std::endl;
    exit(0);
}


int main(int argc, char **argv, char **envp)
{
    // struct timeval tv;
    // tv.tv_sec = 60;
    // tv.tv_usec = 0;
	// web.env = envp;
    webServ web(argv[1]);
	web.setServ_Root(envp);
    web.getCgi().set_transla_path(envp);
    int connection = 0;
    int addrlen = 0;
    int backlog = 10;
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
        if ((retval = select(FD_SETSIZE, &copyset, NULL, NULL, 0)) == -1)
            printerr("Error with select ...");
        else if (retval == 0)
            printerr("Timeout ...");
        else
            engine(web, connection, addrlen);
    }
}
