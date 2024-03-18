# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roylee <roylee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/01 16:22:42 by roylee          #+#    #+#              #
#    Updated: 2024/03/10 14:57:27 by roylee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	gcc
INCLUDE 	=	includes
CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDE) -g -fsanitize=address
RM			=	rm -f
SRCS		=	main.c \
				srcs/error.c srcs/init.c srcs/parser.c srcs/time.c \
				srcs/start.c srcs/print.c srcs/free.c srcs/state.c \
				srcs/lib/ft_atoi.c srcs/lib/ft_strlen.c srcs/lib/ft_isdigit.c \
				srcs/lib/ft_malloc.c

OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
				@echo "Linked into executable \033[0;32mphilo\033[0m."

%.o:			%.c
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
				@echo "Compiling $<."

localclean:
				@$(RM) $(OBJS)
				@echo "Removed object files."

clean:			localclean

fclean:			localclean
				$(RM) $(NAME)
				@echo "Removed executable."

re:				fclean all

.PHONY:			all clean fclean re localclean bonus
