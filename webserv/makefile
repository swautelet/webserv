NAME		= Webserv
SRC			= main.cpp srcs/utils.cpp srcs/socket.cpp srcs/response.cpp srcs/request.cpp srcs/conf.cpp srcs/confData.cpp srcs/location.cpp srcs/autoindex.cpp srcs/webServ.cpp
OBJS	= $(SRC:.cpp=.o)
CXX			= c++
RM			= rm -f
FLAGS		= -Wall -Wextra -Werror -fsanitize=address -g3 -std=c++98 -I   .

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(FLAGS) -o $(NAME) $(OBJS)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(OBJS)

re:			fclean all

.PHONY:		all clean fclean re