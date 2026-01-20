# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2026/01/14 20:28:43 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC				=	main.c mini_map.c ft_free.c set_player.c put_ray.c get_file.c\
					get_info.c get_map.c parser.c utils.c ray_caster.c move.c game_loop.c\
					mouse_keys.c line.c init_mlx.c init_imgs.c frees_exit.c move_util.c\
					ray_caster_utils.c get_color.c my_pixel_put.c put_img.c put_mini_imgs.c
SRC_BONUS		=	main_bonus.c mini_map_bonus.c ft_free_bonus.c set_player_bonus.c put_ray_bonus.c get_file_bonus.c\
					get_info_bonus.c get_map_bonus.c parser_bonus.c utils_bonus.c ray_caster_bonus.c move_bonus.c\
					mouse_keys_bonus.c line_bonus.c init_mlx_bonus.c init_imgs_bonus.c frees_exit_bonus.c move_util_bonus.c\
					ray_caster_utils_bonus.c get_color_bonus.c my_pixel_put_bonus.c put_img_bonus.c put_mini_imgs_bonus.c
SRCS			=	$(addprefix $(PRE_SRC), $(SRC))
PRE_SRC			=	srcs/
SRCS_BONUS		=	$(addprefix $(PRE_SRC_BONUS), $(SRC_BONUS))
PRE_SRC_BONUS	=	b_srcs/
PRE_HEAD_BONUS	=	b_header/
PRE_HEAD		=	header/
HEAD			=	cubed.h libft.h parser.h
HEAD_BONUS		=	cubed_bonus.h libft_bonus.h parser_bonus.h
HEADS			=	$(addprefix $(PRE_HEAD), $(HEAD))
HEADS_BONUS		=	$(addprefix $(PRE_HEAD_BONUS), $(HEAD_BONUS))
BONUS			=	_bonus
NAME			=	cub3D
NAME_BONUS		=	$(addprefix $(NAME), $(BONUS))
CFLAGS			=	-Wall -Wextra -Werror -g
OBJ				=	$(SRC:.c=.o)
OBJ_BONUS		=	$(SRC_BONUS:.c=.o)
PRE_OBJ			=	obj/
OBJS			=	$(addprefix $(PRE_OBJ), $(OBJ))
PRE_OBJ_BONUS	=	b_obj/
OBJS_BONUS		= 	$(addprefix $(PRE_OBJ_BONUS), $(OBJ_BONUS))
RM				=	rm -fr
CC				= 	cc
Lflags			=	-Lmlx -lmlx -lX11 -lXext  -lm 
MAKEFLAGS		+= --no-print-directory

all:		$(NAME)

$(PRE_OBJ)%.o:$(PRE_SRC)%.c $(HEADS)
			(cd libft && make all)
			mkdir -p $(PRE_OBJ)
			$(CC) $(CFLAGS) -I $(PRE_HEAD) -o $@ -c $<

$(NAME):	$(OBJS)
			cc $(CFLAGS) -I $(PRE_HEAD) $(OBJS) -o $(NAME) ./libft/libft.a  $(Lflags)

clean: 
			(cd libft && make clean)
			$(RM) $(OBJS) $(PRE_OBJ)
			$(RM) $(OBJS_BONUS) $(PRE_OBJ_BONUS)

fclean: 	clean
			(cd libft && make fclean)
			$(RM) $(NAME) $(PRE_OBJ) $(NAME_BONUS)

speed:		$(OBJS)
			cc $(CFLAGS) -DMOVE=2 -I $(PRE_HEAD) $(SRCS) -o $(NAME) ./libft/libft.a  $(Lflags)

$(PRE_OBJ_BONUS)%.o:$(PRE_SRC_BONUS)%.c $(HEADS_BONUS)
			(cd libft && make all)
			mkdir -p $(PRE_OBJ_BONUS)
			$(CC) $(CFLAGS) -I $(PRE_HEAD_BONUS) -o $@ -c $<

$(NAME_BONUS): $(OBJS_BONUS)
			cc $(CFLAGS) -DMOVE=1  -I $(PRE_HEAD_BONUS) $(OBJS_BONUS) -o $(NAME_BONUS) ./libft/libft.a  $(Lflags)

bonus:		$(NAME_BONUS)

re:			fclean all
			

.PHONY:		all clean fclean re
