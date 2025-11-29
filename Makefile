# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mehras <mehras@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2025/11/28 07:27:25 by mehras           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	main.c
SRCS		=	${addprefix ${PRE_SRC}, ${SRC}}
PRE_SRC		=	srcs/
HEAD		=	header/ -I/usr/include -O3 -I/home/mehras/mlx
NAME		=	cubed
CFLAGS		=	-Wall -Wextra -Werror -g
OBJ			=	${SRC:.c=.o}
PRE_OBJ		=	obj/
OBJS		=	${addprefix ${PRE_OBJ}, ${OBJ}}
RM			=	rm -fr
CC			= 	cc
Lflags		= -Lmlx -lmlx -lX11 -lXext -lXfixes -lXrender -lXrandr -lm -lz
MAKEFLAGS	+= --no-print-directory

all:		${NAME}

$(PRE_OBJ)%.o:$(PRE_SRC)%.c
			(cd libft && make all)
			mkdir -p $(PRE_OBJ)
			${CC} ${CFLAGS} -I ${HEAD} -o $@ -c $<
${NAME}:	${OBJS}
			cc ${CFLAGS} -I ${HEAD} ${OBJS} -o ${NAME} ./libft/libft.a  $(Lflags)

clean: 
			(cd libft && make clean)
			${RM} ${OBJS} $(PRE_OBJ)

fclean: 	clean
			(cd libft && make fclean)
			${RM} ${NAME} $(PRE_OBJ)

speed:		$(OBJS)
			cc ${CFLAGS} -DMOVE=2 -I ${HEAD} ${SRCS} -o ${NAME} ./libft/libft.a  $(Lflags)


re:			fclean all
			

.PHONY:		all clean fclean re
