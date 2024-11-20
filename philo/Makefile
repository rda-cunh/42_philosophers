# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rda-cunh <rda-cunh@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 23:22:38 by rda-cunh          #+#    #+#              #
#    Updated: 2024/11/20 02:03:22 by rda-cunh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/check_args.c $(SRC_DIR)/initialization.c \
		$(SRC_DIR)/simulation.c $(SRC_DIR)/exit.c $(SRC_DIR)/utils.c			 
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
