/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:39:31 by mehras            #+#    #+#             */
/*   Updated: 2026/01/08 12:33:29 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed_bonus.h"

void	free_imgs(t_mlx *mlx)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	j = -1;
	if (mlx->mini.img)
		mlx_destroy_image(mlx->mlx, mlx->mini.img);
	if (mlx->game.img)
		mlx_destroy_image(mlx->mlx, mlx->game.img);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (mlx->text[i][j].img)
				mlx_destroy_image(mlx->mlx, mlx->text[i][j].img);
	}
}

void	free_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (!mlx->mlx)
		return ;
	if (mlx->win)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx->win = NULL;
	}
	free_imgs(mlx);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	mlx->mlx = NULL;
}

void	free_cube(t_cubed *cube)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	if (cube->map)
		ft_free(cube->map);
	if (cube->mini_map)
		ft_free(cube->mini_map);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (cube->xpm[i][j])
				free(cube->xpm[i][j]);
	}
	free_mlx(cube->mlx);
}

void	free_and_exit(t_cubed *cube, int fd, char *str)
{
	free_cube(cube);
	if (fd == 2)
		ft_putendl_fd("Error", fd);
	if (str)
		ft_putendl_fd(str, fd);
	exit (fd - 1);
}

int	mlx_exit(void *in)
{
	t_cubed	*cube;

	cube = (t_cubed *)in;
	free_and_exit(cube, 1, "DONE!");
	return (1);
}
