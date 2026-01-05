/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:40:33 by mehras            #+#    #+#             */
/*   Updated: 2026/01/04 19:33:46 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed.h"

ssize_t	offset_cal(t_mlx *mlx, t_ray *ray, ssize_t offset, float line_len)
{
	return (roundf((float)mlx->text[ray->opt_face][(int)(mlx->frame / 2)].height
			* (float)offset / line_len
			+ ((float)(mlx->text[ray->opt_face][(int)(mlx->frame / 2)].height) / 2.0f)));
}

float	cal_line_len(t_ray *ray, t_cubed *cube, t_img *game)
{
	float	dist_opt;
	float	ray_offset;

	ray_offset = ray->rot - ray->pa;
	if (ray_offset < 0)
		ray_offset += (2 * cube->pie);
	else if (ray_offset > 2 * cube->pie)
		ray_offset -= (2 * cube->pie);
	dist_opt = ray->dist_opt * cos(ray_offset);
	return ((float)MINISQ * (float)game->height / dist_opt);
}

ssize_t	put_ray_util(t_ray *ray, t_mlx *mlx)
{
	float	frac_x;

	frac_x = 0;
	if (ray->opt_face == N || ray->opt_face == S)
	{
		while (ray->r_x && ray->r_x >= MINISQ)
			ray->r_x = ray->r_x - (float)MINISQ;
		frac_x = ray->r_x;
	}
	else
	{
		while (ray->r_y && ray->r_y >= MINISQ)
			ray->r_y = ray->r_y - (float)MINISQ;
		frac_x = ray->r_y;
	}
	if (ray->opt_face == E || ray->opt_face == N)
		return (mlx->text[ray->opt_face][(int)(mlx->frame / 2)].width - frac_x
			* mlx->text[ray->opt_face][(int)(mlx->frame / 2)].width / MINISQ);
	else
		return (frac_x * mlx->text[ray->opt_face][(int)(mlx->frame / 2)].width / MINISQ);
}

void	put_ray_util2(t_mlx *mlx, t_putray *putray, t_ray *ray, t_img *game)
{
	my_pixel_put(game, game->width - ray->i - 1, putray->j - putray->offset,
		get_color_xpm(&mlx->text[ray->opt_face][(int)(mlx->frame / 2)], putray->x,
			offset_cal(mlx, ray, -putray->offset, putray->line_len)));
	my_pixel_put(game, game->width - ray->i - 1, putray->j + putray->offset,
		get_color_xpm(&mlx->text[ray->opt_face][(int)(mlx->frame / 2)], putray->x,
			offset_cal(mlx, ray, putray->offset, putray->line_len)));
}

void	put_ray(t_cubed *cube, t_mlx *mlx, t_ray *ray)
{
	t_img		*game;
	t_putray	putray;

	game = &mlx->game;
	putray.line_len = cal_line_len(ray, cube, game);
	putray.j = game->height / 2;
	putray.offset = -1;
	putray.x = put_ray_util(ray, mlx);
	while ((++putray.offset + putray.j) < game->height
		&& (putray.j - putray.offset) >= 0)
	{
		if (putray.offset < putray.line_len / 2.0f)
			put_ray_util2(mlx, &putray, ray, game);
		else
		{
			my_pixel_put(game, game->width - ray->i - 1,
				putray.j + putray.offset, cube->floor);
			my_pixel_put(game, game->width - ray->i - 1,
				putray.j - putray.offset, cube->head);
		}
	}
}
