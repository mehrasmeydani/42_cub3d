/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:22:54 by mehras            #+#    #+#             */
/*   Updated: 2025/12/19 00:30:05 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

static void	x_ops(t_player *player, float cosine, bool i)
{
	if (i)
	{
		player->x_i++;
		player->x_f = player->x_f - 1 + cosine;
	}
	else
	{
		player->x_i--;
		player->x_f = player->x_f + 1 + cosine;
	}
}

void	x_op_util(t_cubed *cube, t_player *player, float cosine, bool i)
{
	if (i)
	{
		if (cube->map[player->y_i][player->x_i + 1] != '1'
			&& player->x_f + cosine > 1)
			x_ops(player, cosine, 1);
		else if (cube->map[player->y_i][player->x_i + 1] != '1')
			player->x_f += cosine;
		else
			player->x_f = 0.95;
	}
	else
	{
		if (cube->map[player->y_i][player->x_i - 1] != '1'
			&& player->x_f + cosine < 0)
			x_ops(player, cosine, 0);
		else if (cube->map[player->y_i][player->x_i - 1] != '1')
			player->x_f += cosine;
		else
			player->x_f = 0.05;
	}
}

static void	y_ops(t_player *player, float sine, bool i)
{
	if (i)
	{
		player->y_i++;
		player->y_f = player->y_f - 1 - sine;
	}
	else
	{
		player->y_i--;
		player->y_f = player->y_f + 1 - sine;
	}
}

void	y_op_util(t_cubed *cube, t_player *player, float sine, bool i)
{
	if (i)
	{
		if (cube->map[player->y_i + 1][player->x_i] != '1'
			&& player->y_f - sine > 1)
			y_ops(player, sine, 1);
		else if (cube->map[player->y_i + 1][player->x_i] != '1')
			player->y_f -= sine;
		else
			player->y_f = 0.95;
	}
	else
	{
		if (cube->map[player->y_i - 1][player->x_i] != '1'
			&& player->y_f - sine < 0)
			y_ops(player, sine, 0);
		else if (cube->map[player->y_i - 1][player->x_i] != '1')
			player->y_f -= sine;
		else
			player->y_f = 0.05;
	}
}
