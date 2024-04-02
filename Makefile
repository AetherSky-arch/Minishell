NAME = minishell
SRCS := srcs/main.c \
		srcs/ft_split.c \
		srcs/format_prompt.c \
		srcs/format_prompt_utils.c \
		srcs/type.c \
		srcs/temp.c

OBJS = ${SRCS:.c=.o}

CC = cc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3

LIBFLAGS = -Llibft -lft -lreadline -lncurses

INCLUDES = -I includes -I libft

all: libft ${OBJS} ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

libft:
	cd libft ; make

$(NAME): ${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${LIBFLAGS} -o ${NAME}

clean:
	cd libft ; make clean
	${RM} ${OBJS}

fclean:	clean
	cd libft ; make fclean
	${RM} ${NAME}

re:	fclean all

.PHONY: clean fclean re all libft
