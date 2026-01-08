/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:21:56 by megardes          #+#    #+#             */
/*   Updated: 2026/01/08 12:28:53 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed_bonus.h"
#include <stddef.h>

bool	execute(t_cubed *cube)
{
	t_mlx	*mlx;

	mlx = cube->mlx;
	set_player(cube);
	init_mlx(cube, mlx);
	mlx_loop(mlx->mlx);
	return (1);
}

void	init_main(t_cubed *cube, t_parser *parser, t_player *player, t_mlx *mlx)
{
	ft_bzero(parser, sizeof(t_parser));
	ft_bzero(cube, sizeof(t_cubed));
	ft_bzero(mlx, sizeof(t_mlx));
	ft_bzero(player, sizeof(t_player));
	cube->player = player;
	cube->mlx = mlx;
	cube->pie = 3.141592653589793;
	cube->moving.y = -1;
}

void	set_parser_to_cube(t_cubed *cube, t_parser *pars)
{
	ssize_t	count;

	count = -1;
	cube->map = pars->map;
	pars->map = NULL;
	cube->max_x = pars->max_x;
	cube->max_y = pars->max_y;
	cube->floor = get_color((float)pars->floor[0] / 255.0f,
			(float)pars->floor[1] / 255.0f,
			(float)pars->floor[2] / 255.0f);
	cube->head = get_color((float)pars->ceiling[0] / 255.0f,
			(float)pars->ceiling[1] / 255.0f,
			(float)pars->ceiling[2] / 255.0f);
	while (++count < 4)
	{
		cube->xpm[W][count] = pars->textures[W][count];
		cube->xpm[S][count] = pars->textures[S][count];
		cube->xpm[N][count] = pars->textures[N][count];
		cube->xpm[E][count] = pars->textures[E][count];
		pars->textures[W][count] = NULL;
		pars->textures[S][count] = NULL;
		pars->textures[N][count] = NULL;
		pars->textures[E][count] = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_cubed		cube;
	t_mlx		mlx;
	t_player	player;
	t_parser	parsers;

	if (argc != 2)
		return (ft_putendl_fd("Error\nExactly one argument required!", 2), 1);
	init_main(&cube, &parsers, &player, &mlx);
	if (parser(argv[1], &parsers) == -1)
		return (1);
	set_parser_to_cube(&cube, &parsers);
	free_map(&parsers);
	if (!mini_map(&cube))
		return (1);
	if (!execute(&cube))
		return (1);
}
