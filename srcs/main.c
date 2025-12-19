/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:21:56 by megardes          #+#    #+#             */
/*   Updated: 2025/12/19 01:23:25 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"
#include <sys/time.h>
#include <time.h>

ssize_t	my_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return (((unsigned int)time.tv_usec ) + (time.tv_sec % 10000000 * 1000000));
}

int	parsing_map(t_cubed *cube)
{
	ssize_t	i;
	ssize_t	j;

	j = 15;
	cube->map = ft_calloc(j, sizeof(char *));
	if (!cube->map)
		return (0);
	i = -1;
	while (++i < j - 1)
	{
		if (i == 0 || i == j - 2)
		{
			cube->map[i] = ft_strdup("11111111111111111111111111111111111111");
			if (!cube->map[i])
				return (ft_free(cube->map), 0);
		}
		else if (i == 1)
		{
			cube->map[i] = ft_strdup("10000000000000000000000000000000000001");
			if (!cube->map[i])
				return (ft_free(cube->map), 0);
		}
		else if (i == j - 3)
		{
			cube->map[i] = ft_strdup("10N00000000000000000000000000000000011");
			if (!cube->map[i])
				return (ft_free(cube->map), 0);
		}
		else
		{
			cube->map[i] = ft_strdup("10000000000000000000000000000000000001");
			if (!cube->map[i])
				return (ft_free(cube->map), 0);
		}
	}
	cube->max_y = 14;
	cube->max_x = ft_strlen(cube->map[0]);
	return (1);
}


void	my_pixel_put(t_img *img, ssize_t x, ssize_t y, uint32_t color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(uint32_t*)dst = color;
}

uint32_t get_color(float r, float g, float b)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t blue;

	red = (uint8_t)roundf(((RED >> 16) & 0xFF) * r);
	green = (uint8_t)roundf(((GRN >> 8)  & 0xFF) * g);
	blue = (uint8_t)roundf((BLU & 0xFF) * b);
	return ((red << 16) | (green << 8) | blue);
}

void	fill_map(t_img *img)
{
	ssize_t	i;
	ssize_t	x;
	ssize_t	y;

	y = -1;
	x = -1;
	i = -1;
	while (++i < img->border)
	{
		x = -1;
		while (++x < img->width)
		{
			my_pixel_put(img, x, i, get_color(0.5, 0.5, 0.5));
			my_pixel_put(img, x, img->height - i, get_color(0.5, 0.5, 0.5));
		}
		y = -1;
		while (++y < img->height)
		{
			my_pixel_put(img, i, y, get_color(0.5, 0.5, 0.5));
			my_pixel_put(img, img->width - i, y, get_color(0.5, 0.5, 0.5));
		}
	}
}

void	mini_put_sq(t_img *mini, ssize_t x, ssize_t y, char c)
{
	ssize_t	j;
	ssize_t	i;

	i = y + mini->border;
	j = x + mini->border;
	if (x % (MINISQ / SCALE) && y % (MINISQ / SCALE))
	{
		if (is_in(c, "ENWS0") != -1)
			my_pixel_put(mini, j, i, get_color(0, 1, 0));
		else if (c == '1')
			my_pixel_put(mini, j, i, get_color(0.2, 0.2, 0.2));
		else
			my_pixel_put(mini, j, i, get_color(0, 0, 0));
	}
	else
		my_pixel_put(mini, j, i, get_color(1, 0, 0));
}

void	put_star_small(t_img *img, ssize_t x, ssize_t y, uint32_t color)
{
	my_pixel_put(img, x, y, color);
	my_pixel_put(img, x + 1, y, color);
	my_pixel_put(img, x - 1, y, color);
	my_pixel_put(img, x, y + 1, color);
	my_pixel_put(img, x, y - 1, color);
}

void	put_star(t_img *img, ssize_t x, ssize_t y, uint32_t color)
{
	my_pixel_put(img, x, y, color);
	my_pixel_put(img, x + 1, y, color);
	my_pixel_put(img, x - 1, y, color);
	my_pixel_put(img, x + 2, y, color);
	my_pixel_put(img, x - 2, y, color);
	my_pixel_put(img, x, y + 1, color);
	my_pixel_put(img, x, y - 1, color);
	my_pixel_put(img, x, y + 2, color);
	my_pixel_put(img, x, y - 2, color);
	my_pixel_put(img, x + 1, y + 1, color);
	my_pixel_put(img, x - 1, y - 1, color);
	my_pixel_put(img, x + 1, y - 1, color);
	my_pixel_put(img, x - 1, y + 1, color);
}

uint32_t	get_color_xpm(t_img *img, ssize_t x, ssize_t y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(uint32_t*)dst);
}

void	mini_put_player(t_img *mini, t_player *player)
{
	t_line	line;

	line.x = player->p_x / SCALE + mini->border;
	line.y = player->p_y / SCALE + mini->border;
	line.len = 25;
	line.rot = player->rad;
	put_line(mini, &line, get_color(1, 1, 1));
	put_star(mini, player->p_x / SCALE + mini->border, player->p_y / SCALE + mini->border, get_color(1, 0, 1));
}

void	set_mini_img(t_cubed *cube, t_mlx *mlx)
{
	ssize_t	i;
	ssize_t j;
	t_img	*mini;

	i = -1;
	(void)cube;
	mini = &mlx->mini;
	fill_map(mini);
	while (cube->mini_map[++i])
	{
		if (i % SCALE == 0)
		{
			j = -1;
			while (cube->mini_map[i][++j])
				if (j % SCALE == 0)
					mini_put_sq(mini, j / SCALE, i / SCALE, cube->mini_map[i][j]);
		}
	}
	mini_put_player(mini, cube->player);
}

void	put_image(t_cubed *cube, t_mlx *mlx)
{
	t_line	line;
	t_img	*game;

	game = &mlx->game;
	mlx_destroy_image(mlx->mlx, game->img);
	ft_bzero(game, sizeof(*game));
	if (!init_game(cube, mlx))
		free_and_exit(cube, 2, "malloc fail");
	if (cube->mini)
		set_mini_img(cube, cube->mlx);
	ray_cal(cube, &line, cube->player);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->game.img, 0, 0);
	if (cube->mini)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->mini.img, 0, 0);
}

bool	execute(t_cubed *cube)
{
	t_mlx	*mlx;

	mlx = cube->mlx;
	set_player(cube);
	init_mlx(cube, mlx); // add check
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
	cube->map = pars->map;
	pars->map = NULL;
	cube->max_x = pars->max_x;
	cube->max_y = pars->max_y;
	cube->floor = get_color((float)pars->floor[0] / 255.0f, (float)pars->floor[1] / 255.0f, (float)pars->floor[2] / 255.0f);
	cube->head = get_color((float)pars->ceiling[0] / 255.0f, (float)pars->ceiling[1] / 255.0f, (float)pars->ceiling[2] / 255.0f);
	cube->xpm[W] = pars->textures[W];
	cube->xpm[S] = pars->textures[S];
	cube->xpm[N] = pars->textures[N];
	cube->xpm[E] = pars->textures[E];
	pars->textures[W] = NULL;
	pars->textures[S] = NULL;
	pars->textures[N] = NULL;
	pars->textures[E] = NULL;
}

int	main(int argc, char **argv)
{
	t_cubed		cube;
	t_mlx		mlx;
	t_player	player;
	t_parser	parsers;

	if (argc != 2)
		return (1);
	init_main(&cube, &parsers, &player, &mlx);
	if (parser(argv[1], &parsers) == -1)
		return (1);
	set_parser_to_cube(&cube, &parsers);
	free_map(&parsers);
	if (!mini_map(&cube))
		return (1);
	puts("done with parser");
	if (!execute(&cube))
		return (1);
}

