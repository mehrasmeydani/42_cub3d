/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:40:29 by mehras            #+#    #+#             */
/*   Updated: 2025/12/18 23:40:30 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

void	y_op(t_cubed *cube, t_player *player, float sine)
{
	if (player->y_f - sine > 0.95)
	{
		if (cube->map[player->y_i + 1][player->x_i] != '1' && player->y_f - sine > 1)
		{
			player->y_i++;
			player->y_f = player->y_f - 1 - sine;
		}
		else if (cube->map[player->y_i + 1][player->x_i] != '1')
			player->y_f -= sine;
		else
			player->y_f = 0.95;
	}
	else if (player->y_f - sine < 0.05)
	{
		if (player->y_f - sine < 0 && cube->map[player->y_i - 1][player->x_i] != '1')
		{
			player->y_i--;
			player->y_f = player->y_f + 1 - sine;
		}
		else if (cube->map[player->y_i - 1][player->x_i] != '1')
			player->y_f -= sine;
		else
			player->y_f = 0.05;
	}
	else
		player->y_f -= sine;
	player->p_y = round(((float)(player->y_i) + player->y_f) * (float)MINISQ);
}

void	x_op(t_cubed *cube, t_player *player, float cosine)
{
	if (player->x_f + cosine > 0.95)
	{
		if (cube->map[player->y_i][player->x_i + 1] != '1' && player->x_f + cosine > 1)
		{
			player->x_i++;
			player->x_f = player->x_f - 1 + cosine;
		}
		else if (cube->map[player->y_i][player->x_i + 1] != '1')
			player->x_f += cosine;
		else
			player->x_f = 0.95;
	}
	else if (player->x_f + cosine < 0.05)
	{
		if (cube->map[player->y_i][player->x_i - 1] != '1' && player->x_f + cosine < 0)
		{
			player->x_i--;
			player->x_f = player->x_f + 1 + cosine;
		}
		else if (cube->map[player->y_i][player->x_i - 1] != '1')
			player->x_f += cosine;
		else
			player->x_f = 0.05;
	}
	else
		player->x_f += cosine;
	player->p_x = round(((float)(player->x_i) + player->x_f) * (float)MINISQ);
}

void turn(t_cubed *cube, t_player *player, bool left)
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
