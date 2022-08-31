//variable for cgi

//AUTH_TYPE, CONTENT_LENGTH, CONTENT_TYPE, GATEWAY_INTERFACE, PATH_INFO, PATH_TRANSLATED, QUERY_STRING, REMOTE_ADDR, REMOTE_HOST, REMOTE_IDENT, REMOTE_USER, REQUEST_METHOD, SCRIPT_NAME, SERVER_NAME, SERVER_PORT, SERVER_PROTOCOL et SERVER_SOFTWARE

#ifndef CGI_HPP
#define CGI_HPP

#include "header.hpp"

enum APPLI{
	NOTFOUND = 0,
	PHP = 1,

};

class Cgi{
	public:
		Cgi();
		~Cgi();
		std::string& getPath(std::string& req_file);
		const std::vector<std::string>& getEnv() const;
		const std::vector<std::string>& getArg() const;
		const std::string& getFullpath() const;
		void	setFullpath(webServ& web, confData& conf);
		void	start_script();
		void	setEnv(webServ& web, confData& conf);

	private:
	std::map<std::string, std::string> pathmap;
	std::vector<std::string> env;
	std::vector<std::string> arg;
	std::string body;
	std::string empty;
	std::vector<std::string> fullpath;
	
};

#endif
