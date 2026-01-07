/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:40:13 by mehras            #+#    #+#             */
/*   Updated: 2026/01/07 16:55:24 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed.h"

bool	init_game(t_cubed *cube, t_mlx *mlx)
{
	t_img	*game;

	(void)cube;
	game = &mlx->game;
	game->border = 0;
	game->height = mlx->y_win;
	game->width = mlx->x_win;
	game->img = mlx_new_image(mlx->mlx, game->width, game->height);
	if (!game->img)
		return (0);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->addr)
		return (0);
	return (1);
}

bool	init_text_2(t_cubed *cube, t_mlx *mlx, int i, int j)
{
	t_img	*text;

	text = &mlx->text[i][j];
	text->border = 0;
	text->height = 0;
	text->width = 0;
	text->img = mlx_xpm_file_to_image(mlx->mlx, cube->xpm[i][j],
			&text->width, &text->height);
	if (!text->img)
		return (0);
	text->addr = mlx_get_data_addr(text->img, &text->bits_per_pixel,
			&text->line_length, &text->endian);
	if (!text->addr)
		return (0);
	return (1);
}

bool	init_text(t_cubed *cube, t_mlx *mlx)
{
	ssize_t	i;

	i = -1;
	while (++i < 4)
	{
		if (!init_text_2(cube, mlx, W, i))
			return (0);
		if (!init_text_2(cube, mlx, N, i))
			return (0);
		if (!init_text_2(cube, mlx, E, i))
			return (0);
		if (!init_text_2(cube, mlx, S, i))
			return (0);
	}
	return (1);
}

bool	init_mini_map(t_cubed *cube, t_mlx *mlx)
{
	t_img	*mini;

	mini = &mlx->mini;
	mini->border = (MINISQ / SCALE) / 4;
	mini->height = cube->max_y * MINISQ / SCALE + 2 * mini->border;
	mini->width = cube->max_x * MINISQ / SCALE + 2 * mini->border;
	mini->img = mlx_new_image(mlx->mlx, mini->width, mini->height);
	if (!mini->img)
		return (0);
	mini->addr = mlx_get_data_addr(mini->img, &mini->bits_per_pixel,
			&mini->line_length, &mini->endian);
	if (!mini->addr)
		return (0);
	return (1);
}

void	init_imgs(t_cubed *cube, t_mlx *mlx)
{
	if (!init_mini_map(cube, mlx))
		return (free_and_exit(cube, 2, "mini img failed"));
	if (!init_game(cube, mlx))
		return (free_and_exit(cube, 2, "game img failed"));
	if (!init_text(cube, mlx))
		return (free_and_exit(cube, 2, "textures img failed"));
}
