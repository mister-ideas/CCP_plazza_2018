##
## EPITECH PROJECT, 2019
## CCP_plazza_2018
## File description:
## Makefile
##

SRC_DIR=	src/

SRC=		$(SRC_DIR)main.cpp		\
			$(SRC_DIR)Reception.cpp	\
			$(SRC_DIR)Pizza.cpp

OBJ=		$(SRC:.cpp=.o)

NAME=		plazza

CXXFLAGS=	-Wall -Wextra -Werror -std=c++17

CPPFLAGS=	-I include/

all: 		$(NAME)

$(NAME): 	$(OBJ)
			$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJ)

clean:
			$(RM) $(OBJ)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all fclean clean re