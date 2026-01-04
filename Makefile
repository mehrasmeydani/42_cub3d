# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2026/01/04 17:05:59 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	main.c mini_map.c ft_free.c set_player.c put_ray.c get_file.c\
				get_info.c get_map.c parser.c utils.c ray_caster.c move.c\
				mouse_keys.c line.c init_mlx.c init_imgs.c frees_exit.c move_util.c\
				ray_caster_utils.c get_color.c my_pixel_put.c put_img.c put_mini_imgs.c
SRCS		=	$(addprefix $(PRE_SRC), $(SRC))
PRE_SRC		=	srcs/
SRCS_BONUS	=	$(addprefix $(PRE_SRC_BONUS), $(SRC))
PRE_SRC_BONUS	=	b_srcs/
HEAD_BONUS	=	b_header/
HEAD		=	header/
NAME		=	cubed
NAME_BONUS	=	cubed_bonus
CFLAGS		=	-Wall -Wextra -Werror -g
OBJ			=	$(SRC:.c=.o)
PRE_OBJ		=	obj/
OBJS		=	$(addprefix $(PRE_OBJ), $(OBJ))
PRE_OBJ_BONUS	=	b_obj/
OBJS_BONUS	= 	$(addprefix $(PRE_OBJ_BONUS), $(OBJ))
RM			=	rm -fr
CC			= 	cc
Lflags		=	-Lmlx -lmlx -lX11 -lXext  -lm 
MAKEFLAGS	+= --no-print-directory

all:		$(NAME)

$(PRE_OBJ)%.o:$(PRE_SRC)%.c
			(cd libft && make all)
			mkdir -p $(PRE_OBJ)
			$(CC) $(CFLAGS) -I $(HEAD) -o $@ -c $<

$(NAME):	$(OBJS)
			cc $(CFLAGS) -I $(HEAD) $(OBJS) -o $(NAME) ./libft/libft.a  $(Lflags)

clean: 
			(cd libft && make clean)
			$(RM) $(OBJS) $(PRE_OBJ)
			$(RM) $(OBJS_BONUS) $(PRE_OBJ_BONUS)

fclean: 	clean
			(cd libft && make fclean)
			$(RM) $(NAME) $(PRE_OBJ) $(NAME_BONUS)

speed:		$(OBJS)
			cc $(CFLAGS) -DMOVE=2 -I $(HEAD) $(SRCS) -o $(NAME) ./libft/libft.a  $(Lflags)

$(PRE_OBJ_BONUS)%.o:$(PRE_SRC_BONUS)%.c
			(cd libft && make all)
			mkdir -p $(PRE_OBJ_BONUS)
			$(CC) $(CFLAGS) -I $(HEAD) -o $@ -c $<

bonus:		$(NAME_BONUS) $(OBJS_BONUS)
			cc $(CFLAGS) -I $(HEAD) $(OBJS_BONUS) -o $(NAME_BONUS) ./libft/libft.a  $(Lflags)

re:			fclean all
			

.PHONY:		all clean fclean re
