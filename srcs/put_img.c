/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 02:11:02 by mehras            #+#    #+#             */
/*   Updated: 2026/01/08 13:56:18 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

void	put_image(t_cubed *cube, t_mlx *mlx)
{
	t_line	line;
	t_img	*game;

	game = &mlx->game;
	mlx_destroy_image(mlx->mlx, game->img);
	ft_bzero(game, sizeof(*game));
	if (!init_game(cube, mlx))
		free_and_exit(cube, 2, "Malloc failed");
	if (cube->mini)
		set_mini_img(cube, cube->mlx);
	ray_cal(cube, &line, cube->player);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->game.img, 0, 0);
	if (cube->mini)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->mini.img, 0, 0);
}
