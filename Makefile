LIBFT		= ./libft/libft.a
SRCS		= pipex.c\
			parsing.c
BONUS_SRCS	= pipex_bonus.c\
			parsing_bonus.c
OBJS		= ${SRCS:.c=.o}
BONUS_OBJS	= ${BONUS_SRCS:.c=.o}
NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${MAKE} all -C ./libft
			${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME} 

bonus:		${BONUS_OBJS}
			${MAKE} all -C ./libft
			${CC} ${CFLAGS} ${BONUS_OBJS} ${LIBFT} -o ${NAME} 

all:		$(NAME)

clean:
			${RM} ${OBJS} ${BONUS_OBJS}
			${MAKE} clean -C ./libft

fclean:		clean
			${RM} $(NAME)
			${MAKE} fclean -C ./libft 

re:			fclean all