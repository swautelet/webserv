/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:21:03 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/05 17:53:35 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
#define HEADER_HPP
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "errno.h"
#include "fstream"
#include "sstream"
#include <stdlib.h>
#include "string.h"
#include "socket.hpp"
#include "response.hpp"
#include "request.hpp"
#include "conf.hpp"
#include "confData.hpp"
#include "location.hpp"
#include "autoindex.hpp"
#include <sys/ioctl.h>
#include <dirent.h>
#include <utility>

#include <vector>

#define PATH_ERROR "www/error/404.html"

int printerr(const char *str);
char **ft_split(char *str, char charset);
std::string itoa(int a);
std::string readHTML(confData & conf, std::string file, std::pair<std::string, std::string>);
int check_quote(std::string str);
int check_server_nbr(std::string str, std::string to_find);
int	test(std::string str, std::string c);
char	*test1(std::string str , std::string c);
char	**server_split(std::string str, std::string strset);
void print_tab(char **tab);
std::pair<std::string, std::string> goodIndex(confData & conf, std::string);
std::pair<std::string, std::string> find_base_location(confData & conf, std::string url);
void print(std::string str);

#endif