/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:17:15 by mehras            #+#    #+#             */
/*   Updated: 2025/12/19 01:23:25 by mehras           ###   ########.fr       */
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

void	init_ray(t_cubed *cube, t_img *mini, t_ray *ray, t_line *line)
{
	ft_bzero(ray, sizeof(*ray));
	line->x = cube->player->p_x / SCALE + mini->border;
	line->y = cube->player->p_y / SCALE + mini->border;
	line->len = 0;
	ray->pa = cube->player->rad - ANGLE * RAY_ANGL;
	if (ray->pa < 0)
		ray->pa += (2 * cube->pie);
	else if (ray->pa > 2 * cube->pie)
		ray->pa -= (2 * cube->pie);
	ray->rot = cube->player->rad;
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
