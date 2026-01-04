/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 02:11:02 by mehras            #+#    #+#             */
/*   Updated: 2026/01/04 17:13:14 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed_bonus.h"

void	put_image(t_cubed *cube, t_mlx *mlx)
{
	t_line	line;
	t_img	*game;

	game = &mlx->game;
	mlx_destroy_image(mlx->mlx, game->img);
	ft_bzero(game, sizeof(*game));
	if (!init_game(cube, mlx))
		free_and_exit(cube, 2, "malloc fail");
	if (cube->mini)
		set_mini_img(cube, cube->mlx);
	ray_cal(cube, &line, cube->player);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->game.img, 0, 0);
	if (cube->mini)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->mini.img, 0, 0);
}
