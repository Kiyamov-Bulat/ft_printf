NAME	   = libftprintf.a

INC_DIR	   = .

SRCS	   = ft_printf.c ft_printf_utils.c ft_printf_utils02.c ft_decode_format.c output.c output02.c getlen.c base.c base02.c base03.c base04.c ft_float.c ft_float02.c ft_float03.c ft_float04.c ft_float05.c

OBJS	   = ${SRCS:.c=.o}

DEPS	   = ft_printf.h output.h base.h

CC		   = gcc

CFLAGS	   = -I${INC_DIR}

AR		   = ar rc

.c.o :		${DEPS}
			${CC} ${CFLAGS} -c -MMD $< -o ${<:.c=.o}

all:		${NAME}

bonus:		all

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}

clean:		
			rm -f ${OBJS} *.d

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re

-include *.d
