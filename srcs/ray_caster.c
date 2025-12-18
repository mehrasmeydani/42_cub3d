/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:11:17 by mehras            #+#    #+#             */
/*   Updated: 2025/12/18 23:37:05 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

bool	check_ray(t_ray *ray, t_cubed *cube)
{
	if (ray->mx < MINISQ || ray->my < MINISQ
		|| ray->my > MINISQ * cube->max_y - 1
		|| ray->mx > MINISQ * cube->max_x - 1)
		return (1);
	if (cube->mini_map[ray->my][ray->mx] == '1')
		return (1);
	return (0);
}

void	set_dir_vert(t_ray *ray, t_cubed *cube, t_player *player)
{
	float	a_tan;

	a_tan = 1 / tan(ray->pa);
	if (ray->pa < cube->pie)
	{
		ray->r_y = ((ssize_t)(player->p_y / MINISQ) * MINISQ) - 0.001;
		ray->r_x = (player->p_y - ray->r_y) * a_tan + player->p_x;
		ray->y_offset = -MINISQ;
		ray->x_offset = ray->y_offset * -a_tan;
		ray->v_face = S;
	}
	else if (ray->pa > cube->pie)
	{
		ray->r_y = (ssize_t)(player->p_y / MINISQ) * MINISQ + MINISQ;
		ray->r_x = (player->p_y - ray->r_y) * a_tan + player->p_x;
		ray->y_offset = MINISQ;
		ray->x_offset = ray->y_offset * -a_tan;
		ray->v_face = N;
	}
}

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

void	init_ray(t_cubed *cube, t_img *mini, t_ray *ray, t_line *line)
{
	ft_bzero(ray, sizeof(*ray));
	line->x = cube->player->p_x / scale + mini->border;
	line->y = cube->player->p_y / scale + mini->border;
	line->len = 0;
	ray->pa = cube->player->rad - ANGLE * RAY_ANGL;
	if (ray->pa < 0)
		ray->pa += (2 * cube->pie);
	else if (ray->pa > 2 * cube->pie)
		ray->pa -= (2 * cube->pie);
}

void	set_opt(t_ray *ray)
{
	if (ray->dist_v < ray->dist_h && ray->dist_v != 0)
	{
		ray->r_y = ray->v_y;
		ray->r_x = ray->v_x;
		ray->dist_opt = ray->dist_v;
		ray->opt_face = ray->v_face;
	}
	else
	{
		ray->dist_opt = ray->dist_h;
		ray->opt_face = ray->h_face;
	}
}

void	set_line(t_line *line, t_ray *ray, t_cubed *cube, t_img *mini)
{
	if (ray->pa > cube->pie)
		line->x_end = (ray->r_x) / scale + mini->border;
	else
		line->x_end = roundf(ray->r_x) / scale + mini->border;
	line->y_end = round(ray->r_y) / scale + mini->border;
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
		set_line(line, &ray, cube, mini);
		put_ray(cube, cube->mlx, &ray, player->rad);
		if (cube->mini && cube->ray)
			put_line(mini, line, get_color(0.1, 0.3, 0.8));
		ray.pa += RAY_STEP;
		if (ray.pa > 2 * cube->pie)
			ray.pa -= (2 * cube->pie);
	}
}
