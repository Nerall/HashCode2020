##
## EPITECH PROJECT, 2018
## 
## File description:
## 
##

SRCS 	=	main.cpp


OBJS     =   $(SRCS:.cpp=.o)

CXXFLAGS  +=      -O3 -W -Wall -Wextra -pedantic -std=c++17

NAME 	=	a.out

CXX		= 	g++

$(NAME): 	$(OBJS)
		$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

all:		$(NAME)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re
