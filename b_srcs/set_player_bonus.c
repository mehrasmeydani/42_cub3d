/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:11:02 by mehras            #+#    #+#             */
/*   Updated: 2026/01/04 17:13:14 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed_bonus.h"

void	set_player(t_cubed *cube)
{
	ssize_t	y;
	ssize_t	x;
	ssize_t	rot;
	bool	stop;

	stop = 1;
	y = -1;
	x = 0;
	while (stop && cube->mini_map[++y])
	{
		x = -1;
		while (stop && cube->mini_map[y][++x])
		{
			rot = is_in(cube->mini_map[y][x], "ENWS");
			if (rot != -1)
				stop = 0;
		}
	}
	cube->player->p_x = x;
	cube->player->p_y = y;
	cube->player->x_i = x / MINISQ;
	cube->player->x_f = (float)(x % MINISQ) / (float)(MINISQ);
	cube->player->y_i = y / MINISQ;
	cube->player->y_f = (float)(y % MINISQ) / (float)(MINISQ);
}
