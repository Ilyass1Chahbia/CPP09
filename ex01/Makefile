# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/15 16:17:11 by ilchahbi          #+#    #+#              #
#    Updated: 2025/09/15 16:17:28 by ilchahbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RPN

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SOURCES = main.cpp RPN.cpp

OBJ = $(SOURCES:.cpp=.opp)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.opp: %.cpp RPN.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)	

fclean: clean
	@rm -rf $(NAME)

re: fclean all