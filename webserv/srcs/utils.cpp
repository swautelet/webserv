/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:23:39 by shyrno            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:14 by chly-huc         ###   ########.fr       */
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
    std::ifstream fd;
    std::string tmp;
    DIR *dir;
    struct dirent *ent;
    std::string fullpath;
    std::string tmp_path;
    std::string loc;
    
    
    std::cout << "req_file = " << req_file << std::endl;
    std::cout << "fullpath = " << fullpath << std::endl;

    loc = req_file;
    if (loc.size() > 1)
    {
        if (loc.back() == '/')
            loc.pop_back(); 
        if (isalpha(loc.back()))
            loc = loc.substr(0, loc.rfind('/'));
    }
    std::cout << "loc = " << loc << std::endl;
    if (conf.LocationFinder(loc))
        loc = conf.getGoodLocation(req_file).getLocation_name();
    else
        loc = "/";
    std::cout << "loc = " <<loc << std::endl;
    if (req_file.compare("/"))
    {
        if (req_file.rfind("/"))
            req_file.erase(req_file.rfind("/"));
    }
    if (conf.LocationFinder(loc))
    {
        std::cout << "!" << std::endl;
        tmp = conf.getGoodLocation(loc).getPath();
        tmp_path = tmp + req_file;
    }
    else
    {
        std::cout << "!" << std::endl;
        tmp_path = conf.getPath() + req_file;
    }
    if ((dir = opendir(tmp_path.c_str())) != NULL)
    {
        std::cout << "-------------------------- "<< std::endl;
        std::cout << "[DIR] "<< std::endl;
        std::cout << "tmp path = " << tmp_path << std::endl;
        std::cout << "req_file = " << req_file << std::endl;
        std::cout << "fullpath = " << fullpath << std::endl;
        if (conf.LocationFinder(loc))
        {
            if (!conf.getGoodLocation(loc).getAutoIndex() && conf.getGoodLocation(loc).getIndex().empty())
                fullpath = PATH_ERROR;
            if (conf.getGoodLocation(loc).getAutoIndex())
                printerr("AutoIndex is on, but not implemented yet");
            if (!conf.getGoodLocation(loc).getIndex().empty())
                printerr("Index is on, but not implemented yet"); 
            
        }
        else
        {
            std::cout << "didnt found location" << std::endl;
            if (BaseLocationExist(conf).empty())
            {
                if (!conf.getAutoIndex() && conf.getIndex().empty())
                    fullpath = PATH_ERROR;
                else if (conf.getAutoIndex())
                    printerr("AutoIndex is on, but not implemented yet");
                else if (!conf.getIndex().empty())
                    printerr("Index is on, but not implemented yet");
            }
        }
    }
    else
    {
        if (conf.getGoodLocation(loc).getPath().compare(req_file))
            fullpath = conf.getGoodLocation(loc).getPath() + req_file;
        else
            fullpath = conf.getGoodLocation(loc).getPath();
    }
    std::cout << "tmp path = " << tmp_path << std::endl;
        std::cout << "req_file = " << req_file << std::endl;
        std::cout << "fullpath = " << fullpath << std::endl;
    std::cout << "Final fullpath = " << fullpath << std::endl;
    if (stat(fullpath.c_str(), &info) < 0)
    {
        if (errno == ENOENT)
            fullpath = PATH_ERROR;
    }
    fd.open(fullpath);
    if (!fd.is_open())
    {
        if (fd.good())
            printerr("Error with file opening ... (ReadHTML)");
    }
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