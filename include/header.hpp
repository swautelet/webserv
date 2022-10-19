/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:21:03 by shyrno            #+#    #+#             */
/*   Updated: 2022/10/11 01:29:54 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
#define HEADER_HPP
#include <vector>
#include <map>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
//#include "errno.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
////#include "string.h"
#include "socket.hpp"
#include "response.hpp"
#include "request.hpp"
#include "conf.hpp"
#include "confData.hpp"
#include "location.hpp"
#include "autoindex.hpp"
#include "cgi.hpp"
#include "cgi.hpp"
#include "webServ.hpp"
#include <sys/ioctl.h>
#include <dirent.h>
#include <utility>
//#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <fcntl.h>

#define ERROR_403 "www/error/403.html"
#define ERROR_404 "www/error/404.html"

#define BUFFER_SIZE 10000

int printerr(const char *str);
std::string itoa(int a);
std::string readfile(webServ & web, confData & conf, std::string file);
int check_quote(std::string str);
int check_server_nbr(std::string str, std::string to_find);
int	test(std::string str, std::string c);
char	*test1(std::string str , std::string c);
void print_tab(char **tab);
void remove_spaces(std::string &str);
std::string BaseLocationExist(confData &    conf);
std::string location_exe(confData & conf, std::string req_file);
void	splitstring(std::string str, std::vector<std::string>& vect, char c);
void	splitstring(std::string str, std::vector<std::string>& vect, char c);
int post_element_nbr(std::string str);
std::vector<std::pair<std::string, std::string> > post_arg(std::string str, int nbr);
void post_exe(webServ & web, std::vector<std::pair<std::string, std::string> > post, confData & conf, int nbr);
char** vectstring_tochartable(const std::vector<std::string> vect);
void  free_table(char** table);
std::string	search_value_vect(std::vector<std::string> vect, std::string searched);
int how_many(std::string str);
void print(std::string str);
int str_isspace(std::string str);
int check_location_nbr(std::string str, std::string to_find);
std::string error_parse(int code);
char*   to_char(const std::string& str);
std::string CreateErrorPage(int code);
int is_bodySized(webServ & web, confData & conf);
int ReadWriteProtection(int fd);

#endif

