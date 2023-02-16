LIBFT		= ./libft/libft.a
SRCS		= pipex.c\
			parsing.c\
			error.c
BONUS_SRCS	= pipex_bonus.c\
			parsing_bonus.c\
			error_bonus.c
OBJS		= ${SRCS:.c=.o}
BONUS_OBJS	= ${BONUS_SRCS:.c=.o}
NAME		= pipex
NAME_BONUS	= pipex_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${MAKE} all -C ./libft
			${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME} 

$(NAME_BONUS):		${BONUS_OBJS}
			${MAKE} all -C ./libft
			${CC} ${CFLAGS} ${BONUS_OBJS} ${LIBFT} -o ${NAME_BONUS} 

bonus:		$(NAME_BONUS)

all:		$(NAME) $(NAME_BONUS)

clean:
			${RM} ${OBJS} ${BONUS_OBJS}
			${MAKE} clean -C ./libft

fclean:		clean
			${RM} ./libft/libft.a
			${RM} $(NAME) ${NAME_BONUS}

re:			fclean all