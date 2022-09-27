/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:23:39 by shyrno            #+#    #+#             */
/*   Updated: 2022/09/27 16:03:16 by chly-huc         ###   ########.fr       */
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

std::string location_exe(confData & conf, std::string req_file)
{
    
    std::cout << "SERVER = " << conf.getServName() << std::endl;
    if (!req_file.compare("/") && conf.LocationExist("/"))
        return "/";
	if (req_file.size() >= 1 && req_file[req_file.size() - 1] == '/')
		req_file = req_file.substr(0, req_file.size() - 1);
	while (!req_file.empty() && req_file.find("/") != std::string::npos)
	{
		if (conf.LocationExist(req_file))
        {
            std::cout << conf.LocationFinder(req_file).getLocation_name() << std::endl;
			return conf.LocationFinder(req_file).getLocation_name();
        }
		if (!req_file.rfind('/') && conf.LocationExist(req_file))
			return "/";
		req_file = req_file.substr(0, req_file.rfind('/'));
		if (req_file.empty() && conf.LocationExist("/"))
            return "/";
	}
	return "";
}

std::string index_exe(confData & conf, std::string url, std::string loc)
{
	(void)url;
	std::string index = "";
	struct stat info;
	if (!loc.empty())
	{
		for (unsigned long i = 0; i < conf.getGoodLocation(loc).getIndex().size(); i++)
		{
			index = conf.getGoodLocation(loc).getPath() + "/" + conf.getGoodLocation(loc).getIndex()[i];
			std::cout << "Index location == " << index << std::endl;
			if (stat(index.c_str(), &info) < 0)
			{
				std::cout << errno << std::endl;
				if (errno == ENOENT)
					return "";
			}
			else
				return index;
		}
	}
	else
	{
		for (unsigned long i = 0; i < conf.getIndex().size(); i++)
		{
			index = conf.getPath() + "/" + conf.getIndex()[i];
			std::cout << "Index == " << index << std::endl;
			if (stat(index.c_str(), &info) < 0)
            {
				if (errno == ENOENT)
					return "";
            }
			else
				return index;
		}
	}
	return "";
}

int file_exist(std::string file)
{
    std::ifstream infile(file.c_str());

    if (!infile.good())
        return 0;
    return 1;
}

std::string readHTML(webServ & web, confData & conf, std::string req_file)
{
//  int autodex = 0;
//  struct stat info;
//  struct dirent *ent;
	std::stringstream buff;
    std::string error_path;
    std::ifstream fd;
    std::string tmp;
    DIR *dir;
    std::string fullpath;
	std::string url;
    std::string tmp_path;
    std::string loc;
	std::string index_path;
    
    
	loc = location_exe(conf, req_file);
    
	if (!loc.empty() && conf.LocationExist(loc))
	{
	    web.setMax_body_size(atoi(conf.getGoodLocation(loc).getBodySize().c_str()));
        if (!conf.getGoodLocation(loc).getRedir().empty())
        {
            web.setbool_redir(conf.getGoodLocation(loc).getRedir());
			web.setMax_body_size(atoi(conf.getGoodLocation(loc).getBodySize().c_str()));
            return "";
        }  
		std::cout << "Final location is " << loc <<std::endl;
        std::cout << conf.getGoodLocation(loc).getLocation_name() << std::endl;
        if (!conf.getGoodLocation(loc).getLocation_name().compare(req_file.substr(0, conf.getGoodLocation(loc).getLocation_name().size())) && loc.compare("/"))
        {
            req_file = req_file.substr(conf.getGoodLocation(loc).getLocation_name().size(), req_file.size());
            std::cout << "Found it = " << req_file << std::endl;
            if (!conf.getGoodLocation(loc).getPath().compare("./"))
                url = "." + conf.getGoodLocation(loc).getLocation_name() + req_file;
            else
                url = conf.getGoodLocation(loc).getPath() + conf.getGoodLocation(loc).getLocation_name() + req_file;
        }       
		else if (!conf.getGoodLocation(loc).getPath().compare("./"))
        {
            print("oof");
			url = "." + req_file;
        }
		else
        {
            
            std::cout << "location / ?" << std::endl;
			url = conf.getGoodLocation(loc).getPath() + req_file;
        }
	}
	else
	{
        web.setMax_body_size(atoi(conf.getBodySize().c_str()));
        if (!conf.getRedir().empty())
        {
            web.setbool_redir(conf.getRedir());
            return "";
        }
		std::cout << "No similar location found : base location will be used" <<std::endl;
		if (!conf.getPath().compare("./"))
			url = "." + req_file;
		else
			url = conf.getPath() + req_file;
	}
    std::cout << "!url = " << url << std::endl;
	index_path = index_exe(conf, url, loc);
	if (index_path.empty())
        std::cout << "idk" << std::endl;
    if (file_exist(url) == 0)
    {
        if (conf.LocationExist(loc))
        {
            std::cout << "loc = " << loc <<std::endl;
            std::cout << "eh" << conf.getGoodLocation(loc).getLocation_name() << std::endl;
            std::cout << "wtf !!!!!!!!!!!!!!!! "<< conf.getGoodLocation(loc).getErrorPage() << std::endl;
            std::cout << "wtf-2 "<< conf.getGoodLocation(loc).getBodySize() << std::endl;
            if (!conf.getGoodLocation(loc).getErrorPage().empty())
                fullpath = conf.getGoodLocation(loc).getErrorPage();
            else
                fullpath = ERROR_404;
        }
        else
        {
            if (!conf.getErrorPage().empty())
                fullpath = conf.getErrorPage();
            else
                fullpath = ERROR_404;
        }
    }
    if ((dir = opendir(url.c_str())) != NULL)
    {
        std::cout << "-------------------------- "<< std::endl;
        std::cout << "[DIR] "<< std::endl;
        std::cout << "tmp path = " << tmp_path << std::endl;
        std::cout << "req_file = " << req_file << std::endl;
        std::cout << "fullpath = " << fullpath << std::endl;
        if (conf.LocationExist(loc))
        {
            if (!conf.getGoodLocation(loc).getAutoIndex() && conf.getGoodLocation(loc).getIndex().empty())
                fullpath = ERROR_403;
            if (conf.getGoodLocation(loc).getAutoIndex())
			{
				closedir(dir);
                return web.getAutodex().create_dex(web, conf, url, conf.getGoodLocation(loc));  
			}          
            if (!conf.getGoodLocation(loc).getIndex().empty())
                fullpath = index_path;
            
        }
        else
        {
			web.setMax_body_size(atoi(conf.getBodySize().c_str()));
            std::cout << "didnt found location" << std::endl;
            if (BaseLocationExist(conf).empty())
            {
                if (!conf.getAutoIndex() && conf.getIndex().empty())
                    fullpath = ERROR_403;
                else if (conf.getAutoIndex())
				{
                    std::cout << "HERE" << std::endl;
					web.getRes().setStatus(201);
					web.setMax_body_size(atoi(conf.getBodySize().c_str()));
					closedir(dir);
                    return web.getAutodex().create_dex(web, conf, url, conf.getGoodLocation(loc));
				}
                else if (!conf.getIndex().empty())
                    fullpath = index_path;
            } 
        }
		closedir(dir);
    }
    else
    {
        std::cout << "Not dir" << std::endl;
		if (fullpath.empty())
        {
			fullpath = url;
        }
    }
    // std::cout << "req_file = " << req_file << std::endl;
    // std::cout << "fullpath = " << fullpath << std::endl;
    std::cout << "Final fullpath = " << fullpath << std::endl;
    if (file_exist(url) == 0)
    {
        web.getRes().setContentType(".html");
        fullpath = ERROR_404;
    }
    
    fd.open(fullpath.c_str());
    if (!fd.is_open())
    {
        if (fd.good())
            printerr(" opening ... (ReadHTML)");
    }
    buff << fd.rdbuf();
	web.getRes().setContentType(fullpath);
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
//	int count = 0;
	int find = 0;
	if (str.empty() || to_find.empty())
		return 0;
	while(!str.empty())
	{
        if (str.find(to_find) != std::string::npos)
        {
            find += 1;
            str = str.substr(str.find(to_find) + 1, + str.size());
        }
        else
            break;
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
//	int j  = 0;
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
    unsigned long j = str.size() - 1;
    while (str[i])
    {
        while(isspace(str[i]))
            i++;
        while(isspace(str[j]))
            j--;
        if (i != 0 || j != str.size() - 1)
            str = str.substr(i, j + 1);
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

void	splitstring(std::string str, std::vector<std::string>& vect, char c)
{
	std::string temp = "";
	for(unsigned long i=0; i < str.length(); ++i)
	{
		if(str[i] == c)
		{
			vect.push_back(temp);
			temp = "";
		}
		else
		{
			temp.push_back(str[i]);
		}
	}
	vect.push_back(temp);
}

int post_element_nbr(std::string str)
{
    int count = 0;
    while (!str.empty())
    {
        count++;
        if (str.find('&') == std::string::npos)
            break;
        str = str.substr(str.find('&') + 1, str.size());
    }
    return count;
}

std::vector<std::pair<std::string, std::string> > post_arg(std::string str, int nbr)
{
    std::vector<std::pair<std::string, std::string> > vec(nbr);
    int i = 0;
    std::string tmp;
    std::string cut;
    tmp = str.substr(str.rfind("\n") + 1, str.size());
    while(!tmp.empty())
    {
        cut = tmp.substr(0, tmp.find('&'));
        vec[i].first = cut.substr(0, tmp.find('='));
        vec[i].second = cut.substr(tmp.find('=') + 1, tmp.size());
        tmp = tmp.substr(tmp.find('&') + 1, tmp.size());
        if (tmp.find('&') == std::string::npos)
        {
            vec[i + 1].first = tmp.substr(0, tmp.find('='));
            vec[i + 1].second = tmp.substr(tmp.find('=') + 1, tmp.size());
            return vec;
        }
        i++;
    }
    return vec;
}

void post_exe(webServ & web, std::vector<std::pair<std::string, std::string> > post, confData & conf, int nbr)
{
    DIR *dir;
//    struct dirent *ent;
    std::string url(web.getReq().getUrl());
    
    std::string fullpath(url);
    std::string loc = location_exe(conf, url);
    std::string str = "";
    std::cout << "loc == "<< loc << std::endl; 
    if (loc.empty())
        url = conf.getPath() + "/" + url.substr(1, url.size());
    else
    {
        fullpath = conf.getGoodLocation(loc).getPath() + conf.getGoodLocation(loc).getLocation_name() + url.substr(loc.size(), url.size());
        url = url.substr(1, url.size());
    }
    std::cout << "Post fullpath = " << fullpath << std::endl;
    if (!(dir = opendir(fullpath.c_str())))
    {
        if (fullpath[0] == '.' && fullpath[1] == '/')
            fullpath.erase(0, 2);
        std::ofstream out(fullpath.c_str());
        if (!out.is_open())
        {
            std::cout << errno << std::endl;
        }
        for(unsigned long i = 0; i < post.size(); i++)
        {
            str += post[i].first + "=" + post[i].second;
            if (i + 1 < post.size())
                str += "\n";
        }
        str.resize(nbr);
        out << str;
        out.close();
    }
}

char** vectstring_tochartable(const std::vector<std::string> vect)
{
	char** table = (char**)malloc(sizeof(char*) * (vect.size() + 1));
	table [vect.size()] = NULL;
	for (unsigned long i = 0; i < vect.size(); i++)
	{
		table[i] = (char*)malloc(sizeof(char) * (vect[i].size() + 1));
		for (unsigned long j = 0; j < vect[i].size(); j++)
		{
			table[i][j] = vect[i][j];
		}
		table[i][vect[i].size()] = '\0';
	}
	return table;
}

void	free_table(char** table)
{
	for (int i = 0; table[i]; i++)
	{
		delete (table[i]);
	}
	delete (table);
}

std::string search_value_vect(std::vector<std::string> vect, std::string searched)
{
	std::string ret;
	for (unsigned long i = 0; i < vect.size(); i++)
	{
		if (!vect[i].substr(0, searched.size()).compare(searched))
		{
			ret = vect[i].substr(searched.size() + 1, vect[i].size());
			return ret;
		}
	}
	return ret;
}

void run_api(webServ& web, confData& conf)
{
	web.getCgi().setFullpath(web, conf);
	std::cout << "test" << std::endl;
	web.getCgi().setEnv(web, conf);
	std::cout << "second test "<< std::endl;
	start_script(web.getCgi());
}


void print(std::string str)
{
	std::cout << "print - " << str << std::endl;
}

int str_isspace(std::string str)
{
	if (str.empty())
		return 1;
	for(int i = 0; str[i]; i++)
	{
		if (!isspace(str[i]))
			return 0;
	}
	return 1;
}

int check_location_nbr(std::string str, std::string to_find)
{
    std::string cut;
    int i = 0;
    if (to_find.empty() || str.empty())
        return 0;
    str = str.substr(str.find("\n") + 1, str.size());
    while (!str.empty())
    {
        cut = str.substr(0, str.find("\n"));
        str = str.substr(str.find("\n") + 1, str.size());
        if (!cut.find("server"))
            return i; 
        if (cut.find(to_find) != std::string::npos)
            i++;
    }
    return i;
}

std::string error_parse(int code)
{
    DIR * dir;
    
    struct dirent *ent;
    std::ifstream fd;
    std::stringstream buff;
    struct stat info;
    std::string str;
    (void)code;
    (void)ent;
    (void)info;

    str = itoa(code) + ".html"; 
    if ((dir = opendir("www/error/")) != NULL)
    {
        print("is a file");
        std::cout << "Parsing good error page ... " << std::endl;
        while ((ent = readdir(dir)) != NULL)
        {
            if (!strcmp(ent->d_name, str.c_str()))
            {
                std::string file(ent->d_name);
                fd.open("www/error/" + file);
                if (!fd.is_open())
                {
                    if (fd.good())
                        printerr("Opening ...");
                }
                buff << fd.rdbuf();
                return buff.str();
            }
        }
    }
    return "";
}