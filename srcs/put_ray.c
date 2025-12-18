/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:40:33 by mehras            #+#    #+#             */
/*   Updated: 2025/12/18 23:40:34 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

ssize_t	offset_cal(t_mlx *mlx, t_ray *ray, ssize_t offset, float line_len)
{
	return (round((float)mlx->text[ray->opt_face].height * (float)offset / line_len + ((float)(mlx->text[ray->opt_face].height) / 2.0f)));
}

void	put_ray(t_cubed *cube, t_mlx *mlx, t_ray *ray, float rot)
{
	ssize_t	j;
	ssize_t	offset;
	t_img	*game;
	float	dist_opt;
	float	ray_offset;
	float	line_len;
	
	ray_offset = rot - ray->pa;
	if (ray_offset < 0)
		ray_offset += (2 * cube->pie);
	else if (ray_offset > 2 * cube->pie)
		ray_offset -= (2 * cube->pie);
	dist_opt = ray->dist_opt * cos(ray_offset);
	game = &mlx->game;
	line_len = (float)MINISQ * (float)game->height / dist_opt;
	j = game->height / 2;
	offset = 0;
	while ((offset + j) < game->height && (j - offset) >= 0)
	{
		if (offset < line_len / 2)
		{
			if (ray->opt_face == N || ray->opt_face == S)
			{
				while (ray->r_x && ray->r_x >= MINISQ)
					ray->r_x = ray->r_x - (float)MINISQ;
				float	frac_x = ray->r_x;
				ssize_t x;
				if (ray->opt_face == N)
					x = round((float)mlx->text[ray->opt_face].width - (float)(frac_x / (float)MINISQ * (float)mlx->text[ray->opt_face].width));
				else
					x = round((float)(frac_x / (float)MINISQ) * (float)mlx->text[ray->opt_face].width);
				ssize_t	frac_y_up = offset_cal(mlx, ray, -offset, line_len);
				ssize_t	frac_y_down = offset_cal(mlx, ray, offset, line_len);
				my_pixel_put(game, game->width - ray->i - 1 , j - offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_up));
				my_pixel_put(game, game->width - ray->i - 1 , j + offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_down));
			}
			else
			{
				while (ray->r_y && ray->r_y >= MINISQ)
					ray->r_y = ray->r_y - (float)MINISQ;
				float	frac_x = ray->r_y;
				ssize_t x;
				if (ray->opt_face == E)
				{
					x = round((float)mlx->text[ray->opt_face].width - (float)(frac_x / (float)MINISQ) * (float)mlx->text[ray->opt_face].width);
					ssize_t	frac_y_up = offset_cal(mlx, ray, -offset, line_len);
					ssize_t	frac_y_down = offset_cal(mlx, ray, offset, line_len);
					my_pixel_put(game, game->width - ray->i - 1 , j - offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_up));
					my_pixel_put(game, game->width - ray->i - 1 , j + offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_down));
				}
				else
				{
					x = round((float)(frac_x / (float)MINISQ) * (float)mlx->text[ray->opt_face].width);
					ssize_t	frac_y_up = mlx->text[ray->opt_face].height / line_len * -offset + ((float)(mlx->text[ray->opt_face].height) / 2);
					ssize_t	frac_y_down = mlx->text[ray->opt_face].height / line_len * offset + ((float)(mlx->text[ray->opt_face].height) / 2);
					my_pixel_put(game, game->width - ray->i - 1 , j - offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_up));
					my_pixel_put(game, game->width - ray->i - 1 , j + offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_down));
				}
			}
		}
		else
		{
			my_pixel_put(game, game->width - ray->i - 1 , j + offset, cube->floor);
			my_pixel_put(game, game->width - ray->i - 1 , j - offset, cube->head);
		}
		offset++;
	}
}
