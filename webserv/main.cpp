/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:20:16 by shyrno            #+#    #+#             */
/*   Updated: 2022/10/11 01:56:07 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.hpp"

fd_set fdset, copyset;
std::vector<std::string> ip_vec;
char buffer[10001];
std::string str;
std::vector<int> fdlist;

void fd_update()
{
    FD_ZERO(&copyset);
    copyset = fdset;
}

void setup(webServ & web, int backlog)
{
    for (unsigned long i = 0; i < web.getConf().getNbrServer(); i++)
    {
        int no = 0;
        for(std::vector<std::string>::iterator it = ip_vec.begin(); it != ip_vec.end(); it++)
            if (!it->compare(web.getConf().getConflist(i).getAdress() + ":" + web.getConf().getConflist(i).getPort()))
                no = 1;
        if (!no)
        {
            fdlist.push_back(web.getSock()[i].getFd());
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
    struct timeval tv;
    fd_set fdread;
    fd_set fddump;

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    for(unsigned long i = 0; i < web.getConf().getNbrServer(); i++)
    {
        if (FD_ISSET(web.getSock()[i].getFd(), &copyset))
        {
            int status = 0;
            addrlen = sizeof(web.getSock()[i].serv_address);
            if ((connection = accept(web.getSock()[i].getFd(), (struct sockaddr*)&web.getSock()[i].serv_address, (socklen_t*)&addrlen)) < 0)
                printerr("cannot connect ...");
            if ((fcntl(connection, F_SETFL, O_NONBLOCK)) < 0)
                printerr("Error with fcntl ...");
            int ret = 1;
            memset(buffer, 0, 10000);
            FD_ZERO(&fddump);
	        FD_SET(connection, &fddump);
            while (status == 0)
            {
                FD_ZERO(&fdread);
                fdread = fddump;
                usleep(2000);
                std::cout << "Select ...\n";
                if ((status = select (connection + 1, &fdread, NULL, NULL, &tv)) < 0)
                    printerr("BIG ERROR ...");
            }
            std::cout << "Recv ... : " << ret << std::endl;
            if ((ret = recv(connection, buffer, sizeof(buffer) - 1, 0)) > 0)
            {
                //std::cout << "ret in recv : " << ret << std::endl; 
                buffer[ret] = '\0';
                //std::cout << "recv called : " << ret << std::endl;
                str += buffer;
            }
            if (!str.empty())
            {
                web.getReq().getInfo(connection, str);
                // std::cout << "Info done ..." << std::endl;
                web.getRes().find_method(web, i);
                web.getRes().concat_response(web);
                write(connection, web.getRes().getResponse().c_str(), web.getRes().getResponse().size());
                str = "";
                // std::cout << "uh" << std::endl;
            }
            close(connection);
            return ;
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
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
	// web.env = envp;
    webServ web(argv[1], envp);
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
        usleep(20);
        fd_update();
        if ((retval = select(5 + 1, &copyset, NULL, NULL, &tv)) == -1)
            printerr("Error with select ...");
        else
        {
            //std::cout << "XD\n";
            engine(web, connection, addrlen);
        }
    }
}

// payload too large 