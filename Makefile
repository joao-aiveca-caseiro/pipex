LIBFT		= ./libft/libft.a
SRCS	= pipex.c
OBJS		= ${SRCS:.c=.o}
NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${MAKE} all -C ./libft
			${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME} 

all:		$(NAME)

clean:
			${RM} ${OBJS}
			${MAKE} clean -C ./libft

fclean:		clean
			${RM} $(NAME)
			${MAKE} fclean -C ./libft 

re:			fclean all