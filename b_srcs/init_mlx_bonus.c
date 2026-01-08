/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:40:17 by mehras            #+#    #+#             */
/*   Updated: 2026/01/08 11:50:14 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed_bonus.h"

bool	next_frame(void)
{
	static struct timeval	time;
	struct timeval			time_now;
	ssize_t					j;
	ssize_t					i;

	gettimeofday(&time_now, NULL);
	j = ((unsigned int)time_now.tv_usec / 1000) + (time_now.tv_sec * 1000);
	i = ((unsigned int)time.tv_usec / 1000) + (time.tv_sec * 1000);
	if (j < i || i + FPS < j)
	{
		time = time_now;
		return (0);
	}
	return (1);
}

int	game_loop(void *in)
{
	t_cubed	*cube;
	t_mlx	*mlx;

	cube = (t_cubed *)in;
	mlx = cube->mlx;
	if (next_frame())
		return (0);
	mlx->frame++;
	if (mlx->frame >= 8)
		mlx->frame = 0;
	move(cube, &cube->moving);
	put_image(cube, mlx);
	if (cube->mouse)
		mlx_mouse_move(mlx->mlx, mlx->win, mlx->game.width / 2,
			mlx->game.height / 2);
	return (1);
}

void	hooks(t_cubed *cube, t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, (1L << 0), &mlx_key_press, cube);
	mlx_hook(mlx->win, 3, (1L << 1), &mlx_key_release, cube);
	mlx_hook(mlx->win, 17, 0L, &mlx_exit, cube);
	mlx_loop_hook(mlx->mlx, game_loop, cube);
	mlx_hook(mlx->win, 6, (1L << 6), mouse, cube);
	mlx_mouse_move(mlx->mlx, mlx->win, mlx->game.height / 2,
		mlx->game.width / 2);
}

void	init_mlx(t_cubed *cube, t_mlx *mlx)
{
	t_line	line;

	ft_bzero(&line, sizeof(line));
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (free_and_exit(cube, 2, "mlx failed"));
	mlx_get_screen_size(mlx->mlx, &mlx->x_win, &mlx->y_win);
	if ((float)(mlx->x_win) / (float)(mlx->y_win) > 16.0f / 9.0f)
		mlx->x_win = (float)(mlx->y_win) * 16.0f / 9.0f;
	mlx->win = mlx_new_window(mlx->mlx, mlx->x_win, mlx->y_win, "cub3d");
	if (!mlx->win)
		return (free_and_exit(cube, 2, "win failed"));
	init_imgs(cube, mlx);
	hooks(cube, mlx);
	ray_cal(cube, &line, cube->player);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->game.img, 0, 0);
}
