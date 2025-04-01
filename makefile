# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 14:04:56 by earutiun          #+#    #+#              #
#    Updated: 2025/04/01 14:04:58 by earutiun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# target
NAME = server

# complier and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I.
LFLAGS = -Llibft
LLIBS = -lft

# files
SOURCES = server.c
OBJECTS = $(SOURCES:.c=.o)

# rules
all: $(NAME)

libft:
	$(MAKE) -C ./libft

$(NAME): libft $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES:.c=.o) $(LFLAGS) $(LLIBS) -o $(NAME)

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C ./libft
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
