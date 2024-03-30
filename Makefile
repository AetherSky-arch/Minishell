# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 23:32:02 by caguillo          #+#    #+#              #
#    Updated: 2024/03/30 23:18:27 by caguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCS		=	./srcs/main.c \
				./srcs/ft_split.c \
				./srcs/format_prompt.c \
				./srcs/format_prompt_tools1.c \
				./srcs/libft.c

INCS_SRCS	=	./includes/minishell.h
INCS_DIR	=	-Iincludes

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

OBJS		=	$(SRCS:.c=.o)

%.o:%.c		$(INCS_SRCS)
			$(CC) $(CFLAGS) $(INCS_DIR) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -lreadline -lncurses -o $(NAME)
			
all:		$(NAME)

re: 		fclean all
			
clean:
			rm -f $(OBJS)
			
fclean: 	clean
			rm -f $(NAME)

.PHONY: 	all clean fclean re
