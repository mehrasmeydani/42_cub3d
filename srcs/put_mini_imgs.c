/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_mini_imgs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 01:56:25 by mehras            #+#    #+#             */
/*   Updated: 2026/02/15 18:15:26 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

void	put_star(t_img *img, ssize_t x, ssize_t y, uint32_t color)
{
	my_pixel_put(img, x, y, color);
	my_pixel_put(img, x + 1, y, color);
	my_pixel_put(img, x - 1, y, color);
	my_pixel_put(img, x + 2, y, color);
	my_pixel_put(img, x - 2, y, color);
	my_pixel_put(img, x, y + 1, color);
	my_pixel_put(img, x, y - 1, color);
	my_pixel_put(img, x, y + 2, color);
	my_pixel_put(img, x, y - 2, color);
	my_pixel_put(img, x + 1, y + 1, color);
	my_pixel_put(img, x - 1, y - 1, color);
	my_pixel_put(img, x + 1, y - 1, color);
	my_pixel_put(img, x - 1, y + 1, color);
}

void	mini_put_player(t_img *mini, t_player *player)
{
	t_line	line;

	line.x = player->p_x / SCALE + mini->border;
	line.y = player->p_y / SCALE + mini->border;
	line.len = 15;
	line.rot = player->rad;
	put_line(mini, &line, get_color(1, 1, 1));
	put_star(mini, player->p_x / SCALE + mini->border,
		player->p_y / SCALE + mini->border, get_color(1, 0, 1));
}

void	mini_put_sq(t_img *mini, ssize_t x, ssize_t y, char c)
{
	ssize_t	j;
	ssize_t	i;

	i = y + mini->border;
	j = x + mini->border;
	if (x % (MINISQ / SCALE) && y % (MINISQ / SCALE))
	{
		if (is_in(c, "ENWS0") != -1)
			my_pixel_put(mini, j, i, get_color(0, 1, 0));
		else if (c == '1')
			my_pixel_put(mini, j, i, get_color(0.2, 0.2, 0.2));
		else
			my_pixel_put(mini, j, i, get_color(0, 0, 0));
	}
	else
		my_pixel_put(mini, j, i, get_color(1, 0, 0));
}

void	fill_map(t_img *img)
{
	ssize_t	i;
	ssize_t	x;
	ssize_t	y;

	i = -1;
	while (++i < img->border)
	{
		x = -1;
		while (++x < img->width)
		{
			my_pixel_put(img, x, i, get_color(0.5, 0.5, 0.5));
			my_pixel_put(img, x, img->height - i, get_color(0.5, 0.5, 0.5));
		}
		y = -1;
		while (++y < img->height)
		{
			my_pixel_put(img, i, y, get_color(0.5, 0.5, 0.5));
			my_pixel_put(img, img->width - i, y, get_color(0.5, 0.5, 0.5));
		}
	}
}

void	set_mini_img(t_cubed *cube, t_mlx *mlx)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	len1;
	t_img	*mini;

	i = 0;
	(void)cube;
	mini = &mlx->mini;
	fill_map(mini);
	len1 = -1;
	while (cube->mini_map[++len1])
		;
	while (i < len1 && i / SCALE < mlx->game.height)
	{
		j = 0;
		while (cube->mini_map[i][j] && j / SCALE < mlx->game.width)
		{
			mini_put_sq(mini, j / SCALE, i / SCALE, cube->mini_map[i][j]);
			j += SCALE;
		}
		i += SCALE;
	}
	mini_put_player(mini, cube->player);
}
