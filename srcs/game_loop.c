/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:53:57 by eprottun          #+#    #+#             */
/*   Updated: 2026/01/08 12:54:29 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

int	game_loop(void *in)
{
	t_cubed	*cube;
	t_mlx	*mlx;

	cube = (t_cubed *)in;
	if (next_frame())
		return (0);
	cube->frame++;
	if (cube->frame >= 20)
		cube->frame = 0;
	move(cube, &cube->moving);
	put_image(cube, cube->mlx);
	mlx = cube->mlx;
	if (cube->mouse)
		mlx_mouse_move(mlx->mlx, mlx->win, mlx->game.width / 2,
			mlx->game.height / 2);
	return (1);
}