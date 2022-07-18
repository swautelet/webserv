/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:21:03 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/12 08:35:46 by shyrno           ###   ########.fr       */
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
#include <vector>

int printerr(const char *str);
char **ft_split(char *str, char charset);
std::string itoa(int a);
std::string readHTML(const char *file);
int check_quote(std::string str);
int check_server_nbr(std::string str);


#endif