/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:21:56 by megardes          #+#    #+#             */
/*   Updated: 2025/11/26 15:05:06 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

void	ft_free(char **in)
{
	ssize_t	i;

	i = -1;
	while (in && in[++i])
		free(in[i]);
	free(in);
}

int	parsing_map(t_cubed *cube)
{
	ssize_t	i;
	ssize_t	j;

	j = 10;
	cube->map = ft_calloc(j, sizeof(char *));
	if (!cube->map)
		return (0);
	i = -1;
	while (++i < j - 1)
	{
		if (i == 0 || i == j - 2)
		{
			cube->map[i] = ft_strdup("1111111");
			if (!cube->map[i])
				return (ft_free(cube->map), 0);
		}
		else if (i == 1)
		{
			cube->map[i] = ft_strdup("1E00001");
			if (!cube->map[i])
				return (ft_free(cube->map), 0);
		}
		else
		{
			cube->map[i] = ft_strdup("1000001");
			if (!cube->map[i])
				return (ft_free(cube->map), 0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_cubed		cube;
	t_mlx		mlx;
	t_player	player;

	(void)argv;
	if (argc != 2)
		return (1);
	ft_bzero(&cube, sizeof(t_cubed));
	ft_bzero(&mlx, sizeof(t_mlx));
	ft_bzero(&player, sizeof(t_player));
	cube.player = &player;
	cube.mlx = &mlx;
	if (!parsing_map(&cube))
		return (1);
}



