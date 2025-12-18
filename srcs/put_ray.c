#include "../header/cubed.h"

void	put_ray(t_cubed *cube, t_mlx *mlx, t_ray *ray, int i, float rot)
{
	t_line	line;
	ssize_t	j;
	ssize_t	offset;
	t_img	*game;
	float	dist_opt;
	float	ray_offset;
	
	ray_offset = rot - ray->pa;
	if (ray_offset < 0)
		ray_offset += (2 * cube->pie);
	else if (ray_offset > 2 * cube->pie)
		ray_offset -= (2 * cube->pie);
	dist_opt = ray->dist_opt * cos(ray_offset);
	game = &mlx->game;
	line.len = round((float)MINISQ * (float)game->height / dist_opt);
	j = game->height / 2;
	offset = 0;
	while ((offset + j) < game->height && (j - offset) >= 0)
	{
		if (offset < line.len / 2)
		{
			if (ray->opt_face == N || ray->opt_face == S)
			{
				while (ray->r_x && ray->r_x >= MINISQ)
					ray->r_x = ray->r_x - (float)MINISQ;
				float	frac_x = ray->r_x;
				ssize_t x;
				if (ray->opt_face == N)
					x = (float)mlx->text[ray->opt_face].width - round((float)(frac_x / (float)MINISQ) * (float)mlx->text[ray->opt_face].width);
				else
					x = round((float)(frac_x / (float)MINISQ) * (float)mlx->text[ray->opt_face].width);
				ssize_t	frac_y_up = mlx->text[ray->opt_face].height / line.len * -offset + ((float)(mlx->text[ray->opt_face].height) / 2);
				ssize_t	frac_y_down = mlx->text[ray->opt_face].height / line.len * offset + ((float)(mlx->text[ray->opt_face].height) / 2);
				my_pixel_put(game, game->width - i - 1 , j - offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_up));
				my_pixel_put(game, game->width - i - 1 , j + offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_down));
			}
			else
			{
				while (ray->r_y && ray->r_y >= MINISQ)
					ray->r_y = ray->r_y - (float)MINISQ;
				float	frac_x = ray->r_y;
				ssize_t x;
				if (ray->opt_face == E)
				{
					x = (float)mlx->text[ray->opt_face].width - round((float)(frac_x / (float)MINISQ) * (float)mlx->text[ray->opt_face].width);
					ssize_t	frac_y_up = mlx->text[ray->opt_face].height / line.len * -offset + ((float)(mlx->text[ray->opt_face].height) / 2);
					ssize_t	frac_y_down = mlx->text[ray->opt_face].height / line.len * offset + ((float)(mlx->text[ray->opt_face].height) / 2);
					my_pixel_put(game, game->width - i - 1 , j - offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_up));
					my_pixel_put(game, game->width - i - 1 , j + offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_down));
				}
				else
				{
					x = round((float)(frac_x / (float)MINISQ) * (float)mlx->text[ray->opt_face].width);
					ssize_t	frac_y_up = mlx->text[ray->opt_face].height / line.len * -offset + ((float)(mlx->text[ray->opt_face].height) / 2);
					ssize_t	frac_y_down = mlx->text[ray->opt_face].height / line.len * offset + ((float)(mlx->text[ray->opt_face].height) / 2);
					my_pixel_put(game, game->width - i - 1 , j - offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_up));
					my_pixel_put(game, game->width - i - 1 , j + offset, get_color_xpm(&mlx->text[ray->opt_face], x, frac_y_down));
				}
			}
		}
		else
		{
			my_pixel_put(game, game->width - i - 1 , j + offset, get_color(0, 0.3921568, 0));
			my_pixel_put(game, game->width - i - 1 , j - offset, get_color(0, 0.3921568, 1));
		}
		offset++;
	}
}