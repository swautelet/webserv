/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shyrno <shyrno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 05:49:12 by shyrno            #+#    #+#             */
/*   Updated: 2022/07/12 07:48:07 by shyrno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_HPP
#define CONF_HPP

#include "header.hpp"
#include <vector>

class confData;

class Conf
{
    public:
        Conf();
        ~Conf();
        Conf(const Conf & other);
        void setAddress(char *str);
        void setPath(char *str);
        void setServName(char *str);
        void setMethod(char *str);
        void setIndex(char *str); 
        void parsing(char *path);
    private:
        std::vector<confData> *confList;
        int autoindex;
};


#endif