NAME = libft.a
SRCS := ft_isalpha.c \
       ft_isdigit.c \
       ft_isalnum.c \
       ft_isascii.c \
       ft_isprint.c \
       ft_memset.c \
       ft_bzero.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_strlcpy.c \
       ft_strlcat.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strchr.c \
       ft_strrchr.c \
       ft_strncmp.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_strnstr.c \
       ft_atoi.c \
       ft_substr.c \
       ft_strjoin.c \
       ft_strtrim.c \
       ft_split.c \
       ft_itoa.c \
       ft_ulitoa.c \
       ft_strmapi.c \
       ft_striteri.c \
       ft_putchar_fd.c \
       ft_putstr_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c \
       ft_strdup.c \
	ft_printf.c \
	ft_printf_utils.c \
	hexa_converter.c \
	pointers_converter.c \
	get_next_line.c \
	get_next_line_utils.c \
	double_free.c \
	ft_swap.c \
	double_print.c \
	ft_strcmp.c \
	double_dup.c

BONUS := ft_lstnew.c \
	 ft_lstadd_front.c \
	 ft_lstsize.c \
	 ft_lstlast.c \
	 ft_lstadd_back.c \
	 ft_lstdelone.c \
	 ft_lstclear.c \
	 ft_lstiter.c \
	 ft_lstmap.c

ifeq ($(MAKECMDGOALS), bonus)
SRCS := ${SRCS} ${BONUS}
endif

OBJS = ${SRCS:.c=.o}

OBJ_B = ${BONUS:.c=.o}

CC = cc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3

.c.o:
	${CC} ${CFLAGS} -I . -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	ar rcs ${NAME} ${OBJS}

all bonus: ${NAME}

clean:
	${RM} ${OBJS} ${OBJ_B}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: bonus clean fclean re all
