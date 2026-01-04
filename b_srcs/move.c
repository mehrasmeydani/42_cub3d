/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:40:29 by mehras            #+#    #+#             */
/*   Updated: 2026/01/04 16:29:12 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed.h"

void	y_op(t_cubed *cube, t_player *player, float sine)
{
	if (player->y_f - sine > 0.95)
		y_op_util(cube, player, sine, 1);
	else if (player->y_f - sine < 0.05)
		y_op_util(cube, player, sine, 0);
	else
		player->y_f -= sine;
	player->p_y = roundf(((float)(player->y_i) + player->y_f) * (float)MINISQ);
}

void	x_op(t_cubed *cube, t_player *player, float cosine)
{
	if (player->x_f + cosine > 0.95)
		x_op_util(cube, player, cosine, 1);
	else if (player->x_f + cosine < 0.05)
		x_op_util(cube, player, cosine, 0);
	else
		player->x_f += cosine;
	player->p_x = roundf(((float)(player->x_i) + player->x_f) * (float)MINISQ);
}

void	turn(t_cubed *cube, t_player *player, bool left)
{
	if (left)
	{
		if (player->rad + TURN > cube->pie * 2)
			player->rad = TURN + player->rad - cube->pie * 2;
		else
			player->rad += TURN;
	}
	else
	{
		if (player->rad - TURN < 0)
			player->rad = -TURN + player->rad + cube->pie * 2;
		else
			player->rad -= TURN;
	}
}

void	move(t_cubed *cube, t_move *moving)
{
	if (moving->straight == FORWARD)
	{
		y_op(cube, cube->player, sin(cube->player->rad) / MOVE);
		x_op(cube, cube->player, cos(cube->player->rad) / MOVE);
	}
	else if (moving->straight == BACKWARD)
	{
		y_op(cube, cube->player, sin(cube->player->rad) / MOVE * -1);
		x_op(cube, cube->player, cos(cube->player->rad) / MOVE * -1);
	}
	if (moving->side == LEFT)
	{
		y_op(cube, cube->player, cos(cube->player->rad) / MOVE * -1);
		x_op(cube, cube->player, sin(cube->player->rad) / MOVE);
	}
	else if (moving->side == RIGHT)
	{
		y_op(cube, cube->player, cos(cube->player->rad) / MOVE);
		x_op(cube, cube->player, sin(cube->player->rad) / MOVE * -1);
	}
	if (moving->turn == RIGHT)
		turn(cube, cube->player, 0);
	else if (moving->turn == LEFT)
		turn(cube, cube->player, 1);
}
