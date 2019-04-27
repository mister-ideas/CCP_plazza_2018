##
## EPITECH PROJECT, 2017
## 101pong
## File description:
## maths
##

CC 	= 	g++ -lpthread

RM	= 	rm -f

NAME 	=	plazza

SRCS	=	main.cpp \
		open_shared_mem.cpp \
		reception.cpp \
		kitchen.cpp \
		parsing.cpp \

OBJS	=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)
		$(RM) $(OBJS2)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re
