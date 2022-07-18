NAME		= Webserv
SRC			= main.cpp utils.cpp socket.cpp response.cpp request.cpp conf.cpp confData.cpp
OBJS		= $(SRC:.cpp=.o)
CC			= c++
RM			= rm -f
FLAGS		=  -std=c++98 -I .

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(OBJS)

re:			fclean all

.PHONY:		all clean fclean re