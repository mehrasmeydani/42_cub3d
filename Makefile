# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2025/11/26 14:52:54 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	main.c
SRCS		=	${addprefix ${PRE_SRC}, ${SRC}}
PRE_SRC		=	srcs/
HEAD		=	header/
NAME		=	philo
CFLAGS		=	-Wall -Wextra -Werror
OBJ			=	${SRC:.c=.o}
PRE_OBJ		=	obj/
OBJS		=	${addprefix ${PRE_OBJ}, ${OBJ}}
RM			=	rm -fr
CC			= 	cc
MAKEFLAGS	+= --no-print-directory

all:		${NAME}

$(PRE_OBJ)%.o:$(PRE_SRC)%.c
			(cd libft && make all)
			mkdir -p $(PRE_OBJ)
			${CC} ${CFLAGS} -I ${HEAD} -o $@ -c $<
${NAME}:	${OBJS}
			cc ${CFLAGS} -I ${HEAD} ${SRCS} -o ${NAME} ./libft/libft.a

clean: 
			(cd libft && make clean)
			${RM} ${OBJS} $(PRE_OBJ)

fclean: 	clean
			(cd libft && make fclean)
			${RM} ${NAME} $(PRE_OBJ)

re:			fclean all
			

.PHONY:		all clean fclean re
