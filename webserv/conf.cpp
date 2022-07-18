/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 05:49:14 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/12 07:26:20 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

Conf::Conf()
{

}

Conf::~Conf()
{
        
}

Conf::Conf(const Conf & other)
{
    *this = other;
}

// void Conf::setAddress(char *str)
// {
//     char **split = ft_split(str, ' ');
//     if (!split)
//         return;
//     int i = -1;
//     while(split[1][++i] && split[1][i] != ':')
//         address += split[1][i];
//     while (split[1][++i])
//         port += split[1][i];
//     return;
// }

// void Conf::setPath(char *str)
// {
//     char **split = ft_split(str, ' ');
//     if (!split)
//         return;

//     int i = 1;
//     int j = 0;
//     while(split[i])
//     {
//         while(split[i][j])
//         {
//             if (i >= 2 && j == 0)
//                 path += ' '; 
//             path += split[i][j];
//             j++;
//         }
//         i++;
//         j = 0;
//     }
// }

// void Conf::setServName(char *str)
// {
//     char **split = ft_split(str, ' ');
//     if (!split)
//         return;

//     int i = 1;
//     int j = 0;
//     while(split[i])
//     {
//         while(split[i][j])
//         {
//             if (i >= 2 && j == 0)
//                 serv_name += ' '; 
//             serv_name += split[i][j];
//             j++;
//         }
//         i++;
//         j = 0;
//     }
// }

// void Conf::setMethod(char *str)
// {
//     char **split = ft_split(str, ' ');
//     if (!split)
//         return;

//     int i = 1;
//     int j = 0;
//     while(split[i])
//     {
//         while(split[i][j])
//         {
//             if (i >= 2 && j == 0)
//                 method += ' '; 
//             method += split[i][j];
//             j++;
//         }
//         i++;
//         j = 0;
//     }
// }

// void Conf::setIndex(char *str)
// {
//     char **split = ft_split(str, ' ');
//     if (!split)
//         return;

//     int i = 1;
//     int j = 0;
//     while(split[i])
//     {
//         while(split[i][j])
//         {
//             if (i >= 2 && j == 0)
//                 index += ' '; 
//             index += split[i][j];
//             j++;
//         }
//         i++;
//         j = 0;
//     }
// }

void Conf::parsing(char *path)
{
    
    confList = new std::vector<confData>(4);
    (*confList)[0].parsing(path);
    // buff << fd.rdbuf();
    // setAddress(tmp[1]);
    // setPath(tmp[2]);
    // setServName(tmp[3]);
    // setMethod(tmp[5]);
    // setIndex(tmp[6]);
    //std::cout << confList << std::endl;
}