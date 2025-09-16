# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/16 15:40:12 by ilchahbi          #+#    #+#              #
#    Updated: 2025/09/16 15:40:36 by ilchahbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  PmergeMe

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SOURCES = main.cpp  PmergeMe.cpp

OBJ = $(SOURCES:.cpp=.opp)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.opp: %.cpp  PmergeMe.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)	

fclean: clean
	@rm -rf $(NAME)

re: fclean all