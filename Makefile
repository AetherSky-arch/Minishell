NAME = minishell

SRCS := srcs/main.c \
		srcs/signal.c \
		srcs/check_quotes.c \
		srcs/syntax_checker.c \
		srcs/syntax_checker_utils.c \
		srcs/format_prompt.c \
		srcs/format_prompt_utils.c \
		srcs/format_prompt_utils2.c \
		srcs/format_prompt_utils3.c \
		srcs/format_prompt_utils4.c \
		srcs/split_fprompt.c \
		srcs/tokenizer.c \
		srcs/tokenizer_utils.c \
		srcs/tokenizer_utils2.c \
		srcs/type.c \
		srcs/heredoc_setting.c \
		srcs/files.c \
		srcs/heredoc_to_exec.c \
		srcs/to_exec.c \
		srcs/path.c \
		srcs/exec.c \
		srcs/builtins.c \
		srcs/echo.c \
		srcs/env.c \
		srcs/chd.c \
		srcs/pwd.c \
		srcs/exit.c \
		srcs/export.c \
		srcs/export_utils.c \
		srcs/envvars_manager.c \
		srcs/envvars_utils.c \
		srcs/envvars_utils2.c \
		srcs/unset.c \
		srcs/free_close_exit.c \
		srcs/temp.c \
		srcs/dollar.c \
		srcs/ft_getenv.c
				

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

valgrind: all
		valgrind -q --suppressions=$(PWD)/ignore --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
    	./minishell

.PHONY: clean fclean re all libft
