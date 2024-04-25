# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 19:58:53 by mzelouan          #+#    #+#              #
#    Updated: 2024/04/25 09:59:15 by mzelouan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server
TOOLS = tools.a

HFILES =	./includes/minitalk.h

CFILES =	./utils/ft_atoi.c\
			./utils/ft_print_error.c\
			./utils/ft_putchar_fd.c\
			./utils/ft_putnbr_fd.c\
			./utils/ft_putstr_fd.c\
			./utils/ft_strlen.c\
			./utils/ft_strdup.c\

CLIENT_C =	./src/client.c

SERVER_C =	./src/server.c

OFILES = $(CFILES:.c=.o)
OSERVER = $(SERVER_C:.c=.o)
OCLIENT = $(CLIENT_C:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ac rc
RM = rm -rf

all : $(CLIENT) $(SERVER)

$(CLIENT) :	$(OFILES) $(OCLIENT)
			$(CC) $(CFLAGS) $(OCLIENT) $(OFILES) -o $(CLIENT) 			

$(SERVER) :	$(OFILES) $(OSERVER)
			$(CC) $(CFLAGS) $(OSERVER) $(OFILES) -o $(SERVER)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

re : fclean all

clean : 
		$(RM) $(OFILES) $(OCLIENT) $(OSERVER)

fclean : clean 
		$(RM) $(CLIENT) $(SERVER)

.PHONY : all re clean fclean
