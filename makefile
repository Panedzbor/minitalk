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
CLIENT = client

# complier and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I.
LFLAGS = -Llibft
LLIBS = -lft

# files
SERVER_SRC = server.c serv_utils.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_SRC = client.c client_utils.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# rules
all: $(NAME) $(CLIENT)

libft:
	$(MAKE) -C ./libft

$(NAME): libft $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(LFLAGS) $(LLIBS) -o $(NAME)

$(CLIENT): libft $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LFLAGS) $(LLIBS) -o $(CLIENT)

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C ./libft
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re libft
