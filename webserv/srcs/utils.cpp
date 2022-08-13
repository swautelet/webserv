/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:23:39 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/13 23:16:54 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.hpp"

std::pair<std::string, std::string> find_base_location(confData & conf, std::string url)
{
	for(int x = 0; x < conf.getLocationNbr(); x++)
		if (!conf.getLocation(x).getLocation_name().compare("/"))
			return std::make_pair(url.substr(1, url.size()), conf.getLocation(x).getPath());	
	return std::make_pair(url.substr(1, url.size()), conf.getPath());
}

std::pair<std::string, std::string> goodIndex(confData & conf, std::string url)
{
	int i = -1;
	int index = 0;
	if (!url.compare("/"))
		return std::make_pair(url, conf.getPath());		
	else
	{	
		std::string urlz = url;
		if ((index = urlz.rfind('/')) == 0)
			return find_base_location(conf, urlz);
		urlz = urlz.substr(0, index);
		
		while(++i < conf.getLocationNbr())
		{
			if (!urlz.compare(conf.getLocation(i).getLocation_name()))
			{
				if(!conf.getPath().empty())
					return std::make_pair(urlz,conf.getLocation(i).getPath());
				else
					return std::make_pair(urlz, conf.getPath());
			}
		}
	}
	return std::make_pair("", "");
}

std::string readHTML(confData & conf, std::string req_file, std::pair<std::string, std::string> index) // Need to be change, actually disgusting
{
	int j;
    int autodex = 0;
    struct stat info;
	std::stringstream buff;
    std::string error_path;
    std::string fullpath;
    std::ifstream fd;
    std::string tmp;
    std::cout << req_file << " & " << index.first << " & " << index.second << std::endl;
    std::cout << conf.getPath() + "/" + req_file << std::endl;
    
    if (!req_file.compare("/") || req_file.rfind("/") == req_file.size() - 1)
    {
        std::cout << "This is directory listing ... " << std::endl;
        std::cout << "req_file = " << req_file << std::endl;
        if (!req_file.compare("/"))
        {
            if (conf.LocationFinder("/"))
            {
                if (conf.getGoodLocation("/").getIndex().empty() && !conf.getGoodLocation("/").getAutoIndex())
                    fullpath = PATH_ERROR;    
                fullpath = conf.getGoodLocation("/").getIndex();
            }
            else
                if (conf.getIndex().empty() && !conf.getAutoIndex())
                    fullpath = PATH_ERROR;
        }
    }
    else
    { 
        if (!req_file.empty() && req_file[0] == '/')
            req_file = req_file.substr(1, req_file.size());
        if (!index.first.empty() && index.first[0] == '/')
            index.first = index.first.substr(1, index.first.size());
        std::cout << req_file << " & " << index.first << " & " << index.second << std::endl;
        if (BaseLocationExist(conf).empty())
        {
            fullpath = conf.getPath() + "/" + req_file;
        }
        else
        {
            for (int i = 0; i < conf.getLocationNbr(); i++)
            {
                if (!conf.getLocation(i).getLocation_name().compare("/"))
                {
                    error_path = conf.getLocation(i).getErrorPage();
                    if (!conf.getLocation(i).getPath().compare("./"))
                        fullpath = req_file;
                    else
                        fullpath = conf.getLocation(i).getPath() + "/" +req_file;
                    break;
                }
            }
        }
    }
    std::cout << "req_file = " << req_file << " & " << "fullpath = " << fullpath << std::endl;
    if (req_file.rfind("/") != std::string::npos)
    {
        std::cout << "index or autoindex needed" << std::endl;
    }
    if (conf.LocationFinder(req_file))
    {
        std::cout << "Location found compared to req_file" << std::endl;
        
    }
    fd.open(fullpath);
    if (!fd.is_open())
    {
        if (!fd.good())
            printerr("File not found 2... ");
        printerr("Error with file opening ... (ReadHTML)");
    }
    if (!fd.good())
            printerr("File not found 3... ");
    buff << fd.rdbuf();
    return buff.str();
}

std::string itoa(int a)
{
    std::string ss="";   //create empty string
    while(a)
    {
        int x=a%10;
        a/=10;
        char i='0';
        i=i+x;
        ss=i+ss;      //append new character at the front of the string!
    }
    return ss;
}

int printerr(const char *str)
{
    std::cerr << str << std::endl;
    exit(1);
}

static char	**malloc_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (NULL);
}

static int	count_words(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == c))
			i++;
		if (str[i++] && str[i] != c)
			while (str[i] && str[i] != c)
				i++;
	}
	return (i);
}

static char	*malloc_word(char *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = (char*)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != c)
		word[i] = str[i];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char charset)
{
	int		i;
	char	**tab;

	i = 0;
	if (!str)
		return (NULL);
	tab = (char**)malloc(sizeof(char *) * (count_words(str, charset) + 1));
	if (!tab)
		return (NULL);
	while (*str)
	{
		while (*str && (*str == charset))
			str++;
		if (*str && *str != charset)
		{
			tab[i++] = malloc_word(str, charset);
			if (!tab)
				return (malloc_free(tab));
			while (*str && *str != charset)
				str++;
		}
	}
	tab[i] = NULL;
	return (tab);
}

int check_quote(std::string str) 
{
	int i = -1;
	int open = 0;
	int close = 0;
	while (str[++i])
	{
		if (str[i] == '{')
			open++;
		if (str[i] == '}')
			close++;
	}
	if (close != open)
		return printerr ("Error with configuration file  ...");
	return 1;
}

int check_server_nbr(std::string str, std::string to_find)
{
	int count = 0;
	int find = 0;
	if (str.empty() || to_find.empty())
		return 0;
	while(1)
	{
		count = str.find(to_find, count);
		if (count >= strlen(str.c_str()) - 1 || count == -1)
			break;
		count += 6;
		find += 1;
	}
	return find;
}

int	words(std::string c, std::string str)
{
	int	i = 0, j = 0, nb = 0;
	
	while (str[i])
	{
		if(str[i] && str[i] == c[j])
		{
			while(str[i] && str[i] == c[j])
			{
				i++;
				j++;
			}
			if (c[j] == '\0')
				nb++;
			j = 0;
		}
		i++;
	}
	return (nb);
}

char	*next_string(std::string str , std::string c)
{
	char	*word;
	int		i;
	int	j = 0;
	int stock = 0;

	i = -1;
	while(str[++i])
	{
		if(str[i] && str[i] == c[j] && i > 0)
		{
			while(str[i] && str[i] == c[j])
			{
				i++;
				j++;
			}
			if (c[j] == '\0')
			{
				stock = i - strlen(c.c_str());
				i -= j;
				break;
			}
			j = 0;
		}
		stock = i + 1;
	}
	word = (char*)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (str[++i] && i < stock)
		word[i] = str[i];
	word[i] = '\0';
	return (word);
}

char	**server_split(std::string str, std::string strset)
{
	int		i;
	int j  = 0;
	char	**tab;

	i = 0;
	int nbword = words(strset, str);
	tab = (char**)malloc(sizeof(char *) * nbword + 1);
	if (!tab)
		return (NULL);
	while (i < nbword)
	{
		if (i > 0)	
			str = str.substr(strlen(tab[i - 1]));
		tab[i] = next_string(str, strset);
		if (!tab)
			return (malloc_free(tab));
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void print_tab(char **tab)
{
    int i = 0;
    while(tab[i])
    {
        std::cout << "[i]-> " << i <<  tab[i] << std::endl;
        i++;
    }
}

void print(std::string str)
{
    std::cout << str <<std::endl;
}


char *strnstr(const char *s, const char *find, size_t slen)
{
	char c, sc;
	size_t len;

	if ((c = *find++) != '\0') {
		len = strlen(find);
		do {
			do {
				if (slen-- < 1 || (sc = *s++) == '\0')
					return (NULL);
			} while (sc != c);
			if (len > slen)
				return (NULL);
		} while (strncmp(s, find, len) != 0);
		s--;
	}
	return ((char *)s);
}

void remove_spaces(std::string &str)
{
    int i = 0;
    int j = str.size() - 1;
    while (str[i])
    {
        while(isspace(str[i]))
            i++;
        while(isspace(str[j]))
            j--;
        str = str.substr(i, j);
        break;
    }
}

std::string BaseLocationExist(confData conf)
{
    int i = 0;
    while (i < conf.getLocationNbr())
    {
        if (!conf.getLocation(i).getLocation_name().compare("/"))
            return conf.getLocation(i).getPath();
        i++;
    }
    return "";
}