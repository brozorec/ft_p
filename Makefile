# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/09 12:02:33 by bbarakov          #+#    #+#              #
#    Updated: 2015/03/17 18:18:33 by bbarakov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=			gcc

CFLAGS=		-Wall -Werror -Wextra

SRC1=		dir_server/server.c \
			dir_server/forked_server.c \
			dir_server/ls.c \
			dir_server/pwd.c \
			dir_server/cd.c \
			dir_server/receive_file.c \
			dir_server/send_file.c \
			dir_server/errors.c \

INCL1=		./dir_server

OBJ1=		$(SRC1:.c=.o)

SRC2=		dir_client/client.c \
			dir_client/errors.c \
			dir_client/get_next_line.c \
			dir_client/interaction.c \
			dir_client/receive_file.c \
			dir_client/send_file.c \

OBJ2=		$(SRC2:.c=.o)

INCL2=		./dir_client

LIB=		./libft -lft

all:		serveur client

serveur:	$(OBJ1)
	@make -C ./libft
	@$(CC) $(CFLAGS) -o $@ $^ -I $(INCL1) -L $(LIB)

client:		$(OBJ2)
	@make -C ./libft
	@$(CC) $(CFLAGS) -o $@ $^ -I $(INCL2) -L $(LIB)

%.o:	%.c
	@$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean fclean

clean:
	@make clean -C ./libft
	@rm -rf $(OBJ1) $(OBJ2)

fclean: clean
	@make fclean -C ./libft
	@rm -rf serveur client

re: fclean all
