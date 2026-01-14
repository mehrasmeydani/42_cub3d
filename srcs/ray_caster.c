/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:11:17 by mehras            #+#    #+#             */
/*   Updated: 2026/01/14 11:42:32 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

void	ray_loop(t_cubed *cube, t_ray *ray)
{
	bool	hit;

	hit = 0;
	while (hit == 0)
	{
		ray->mx = ray->r_x;
		ray->my = ray->r_y;
		if (check_ray(ray, cube))
			hit = 1;
		else
		{
			ray->r_x += ray->x_offset;
			ray->r_y += ray->y_offset;
		}
	}
}

void	ray_vert(t_ray *ray, t_player *player, t_cubed *cube)
{
	set_dir_vert(ray, cube, player);
	if (ray->pa == 0.00 || (ray->pa == cube->pie))
		return (ray->r_x = player->p_x, ray->r_y = player->p_y,
			(void)(ray->dist_v = 0));
	ray_loop(cube, ray);
	ray->v_x = ray->r_x;
	ray->v_y = ray->r_y;
	ray->dist_v = hypotf(ray->r_x - (float)player->p_x,
			ray->r_y - (float)player->p_y);
}

void	ray_hor(t_ray *ray, t_player *player, t_cubed *cube)
{
	float	n_tan;

	n_tan = tan(ray->pa);
	if (ray->pa < cube->pie / 2 || ray->pa > cube->pie * 3 / 2)
	{
		ray->r_x = ((ssize_t)(player->p_x / MINISQ) * MINISQ) + MINISQ;
		ray->r_y = (player->p_x - ray->r_x) * n_tan + player->p_y;
		ray->x_offset = MINISQ;
		ray->y_offset = (ray->x_offset) * -n_tan;
		ray->h_face = W;
	}
	else if (ray->pa > cube->pie / 2 && ray->pa < cube->pie * 3 / 2)
	{
		ray->r_x = ((ssize_t)(player->p_x / MINISQ) * MINISQ) - 0.001;
		ray->r_y = (player->p_x - ray->r_x) * n_tan + player->p_y;
		ray->x_offset = -MINISQ;
		ray->y_offset = ray->x_offset * -n_tan;
		ray->h_face = E;
	}
	else
		return (ray->r_x = player->p_x, ray->r_y = player->p_y,
			(void)(ray->dist_h = 0));
	ray_loop(cube, ray);
	ray->dist_h = hypotf(ray->r_x - (float)player->p_x,
			ray->r_y - (float)player->p_y);
}

void	set_line(t_line *line, t_ray *ray, t_img *mini)
{
	line->x_end = roundf(ray->r_x) / SCALE + mini->border;
	line->y_end = roundf(ray->r_y) / SCALE + mini->border;
	line->rot = ray->pa;
}

void	ray_cal(t_cubed *cube, t_line *line, t_player *player)
{
	t_ray	ray;
	t_img	*mini;
	t_img	*game;

	mini = &cube->mlx->mini;
	init_ray(cube, mini, &ray, line);
	game = &cube->mlx->game;
	ray.i = -1;
	while (++(ray.i) < game->width)
	{
		ray_vert(&ray, player, cube);
		ray_hor(&ray, player, cube);
		set_opt(&ray);
		set_line(line, &ray, mini);
		if (!(cube->mini && mini->height >= game->height
				&& game->width - ray.i < mini->width))
			put_ray(cube, cube->mlx, &ray);
		if (cube->mini && cube->ray)
			put_line(mini, line, get_color(0.1, 0.3, 0.8));
		ray.pa += (float)((0.0174533f * ANGLE * 2.0f) / (float)game->width);
		if (ray.pa > 2 * cube->pie)
			ray.pa -= (2 * cube->pie);
	}
}
