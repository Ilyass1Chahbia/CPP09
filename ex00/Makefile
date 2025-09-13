# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/12 15:35:30 by ilchahbi          #+#    #+#              #
#    Updated: 2025/09/12 15:36:36 by ilchahbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = btc

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SOURCES = main.cpp BitcoinExchange.cpp

OBJ = $(SOURCES:.cpp=.opp)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.opp: %.cpp BitcoinExchange.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)	

fclean: clean
	@rm -rf $(NAME)

re: fclean all