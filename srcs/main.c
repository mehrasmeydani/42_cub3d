/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:21:56 by megardes          #+#    #+#             */
/*   Updated: 2025/12/09 01:10:20 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

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
			cube->map[i] = ft_strdup("10W00000000000000000000000000000000011");
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

void	free_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (!mlx->mlx)
		return ;
	if (mlx->mini.img)
		mlx_destroy_image(mlx->mlx, mlx->mini.img);
	if (mlx->win)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx->win = NULL;
	}
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	mlx->mlx = NULL;
}

void	free_cube(t_cubed *cube)
{
	if (cube->map)
	{
		ft_free(cube->map);
	}
	free_mlx(cube->mlx);
}

void	free_and_exit(t_cubed *cube, int fd, char *str)
{
	free_cube(cube);
	if (str)
		ft_putendl_fd(str, fd);
	exit (fd - 1);
}

int	mlx_exit(void *in)
{
	t_cubed *cube;

	cube = (t_cubed *)in;
	free_and_exit(cube, 1, "DONE!");
	return (1);
}

void	y_op(t_cubed *cube, t_player *player, float sine)
{
	if (player->y_f - sine > 0.95)
	{
		if (cube->map[player->y_i + 1][player->x_i] != '1' && player->y_f - sine > 1)
		{
			player->y_i++;
			player->y_f = player->y_f - 1 - sine;
		}
		else if (cube->map[player->y_i + 1][player->x_i] != '1')
			player->y_f -= sine;
		else
			player->y_f = 0.95;
	}
	else if (player->y_f - sine < 0.05)
	{
		if (cube->map[player->y_i - 1][player->x_i] != '1' && player->y_f - sine < 0)
		{
			player->y_i--;
			player->y_f = player->y_f + 1 - sine;
		}
		else if (cube->map[player->y_i - 1][player->x_i] != '1')
			player->y_f -= sine;
		else
			player->y_f = 0.05;
	}
	else
		player->y_f -= sine;
	player->p_y = (ssize_t)(((float)(player->y_i) + player->y_f) * MINISQ);
}

void	x_op(t_cubed *cube, t_player *player, float cosine)
{
	if (player->x_f + cosine > 0.95)
	{
		if (cube->map[player->y_i][player->x_i + 1] != '1' && player->x_f + cosine > 1)
		{
			player->x_i++;
			player->x_f = player->x_f - 1 + cosine;
		}
		else if (cube->map[player->y_i][player->x_i + 1] != '1')
			player->x_f += cosine;
		else
			player->x_f = 0.95;
	}
	else if (player->x_f + cosine < 0.05)
	{
		if (cube->map[player->y_i][player->x_i - 1] != '1' && player->x_f + cosine < 0)
		{
			player->x_i--;
			player->x_f = player->x_f + 1 + cosine;
		}
		else if (cube->map[player->y_i][player->x_i - 1] != '1')
			player->x_f += cosine;
		else
			player->x_f = 0.05;
	}
	else
		player->x_f += cosine;
	player->p_x = (ssize_t)round(((float)(player->x_i) + player->x_f) * MINISQ);
}

void	move(t_cubed *cube, bool dir)
{
	if (dir)
	{
		y_op(cube, cube->player, sin(cube->player->rad) / MOVE);
		x_op(cube, cube->player, cos(cube->player->rad) / MOVE);
	}
	else
	{
		y_op(cube, cube->player, sin(cube->player->rad) / MOVE * -1);
		x_op(cube, cube->player, cos(cube->player->rad) / MOVE * -1);
	}
}

void turn(t_cubed *cube, t_player *player, bool left)
{
	if (left)
	{
		if (player->rad + TURN > cube->pie * 2)
			player->rad = TURN + player->rad - cube->pie * 2;
		else
			player->rad += TURN;
	}
	else
	{
		if (player->rad - TURN < 0)
			player->rad = -TURN + player->rad + cube->pie * 2;
		else
			player->rad -= TURN;
	}
}

int	mlx_key(int key_code, void *in)
{
	t_cubed *cube;

	cube = (t_cubed *)in;
	mlx_clear_window(cube->mlx->mlx, cube->mlx->win);
	if (key_code == XK_Escape)
		mlx_exit(in);
	if (key_code == XK_W || key_code == XK_w)
		move(cube, 1);
	if (key_code == XK_S || key_code == XK_s)
		move(cube, 0);
	if (key_code == XK_A || key_code == XK_a)
		turn(cube, cube->player, 1);
	if (key_code == XK_d || key_code == XK_D)
		turn(cube, cube->player, 0);
	if (key_code == XK_R || key_code == XK_r)
		cube->ray = !cube->ray;
	if (key_code == XK_q || key_code == XK_q)
		cube->mini = !cube->mini;
	if (cube->mini)
		set_mini_img(cube, cube->mlx);
	put_image(cube, cube->mlx);
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
	ssize_t	x;
	ssize_t	y;

	y = -1;
	x = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			if (y < img->border || y > img->height - img->border
				|| x < img->border || x > img->width - img->border)
				my_pixel_put(img, x, y, get_color(0.5 , 0.5, 0.5));
			else if ((y - img->border) % MINISQ < 1 || (y - img->border) % MINISQ - MINISQ > -1
				|| (x - img->border) % MINISQ < 1 || (x - img->border) % MINISQ - MINISQ > -1)
				my_pixel_put(img, x, y, get_color(0.8, 0, 0));
			else
				my_pixel_put(img, x, y, get_color(1, 1, 1));
		}
	}
}

void	mini_put_sq(t_img *mini, ssize_t x, ssize_t y, char c)
{
	ssize_t	j;
	ssize_t	i;

	i = y + mini->border;
	j = x + mini->border;
	if (x % MINISQ && y % MINISQ)
	{
		if (is_in(c, "ENWS0") != -1)
			my_pixel_put(mini, j, i, get_color(0, 1, 0));
		else if (c == '1')
			my_pixel_put(mini, j, i, get_color(0.2, 0.2, 0.2));
		else
			my_pixel_put(mini, j, i, get_color(0, 0, 0));
	}
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

void	put_line(t_img *img, t_line *line, uint32_t color)
{
	ssize_t x = line->x;
	ssize_t y = line->y;


	if (line->len != 0)
	{
		line->x_end = line->x + roundf(cos(line->rot) * line->len);
		line->y_end = line->y - roundf(sin(line->rot) * line->len);
	}

	ssize_t dx = line->x_end - line->x;
	ssize_t dy = line->y_end - line->y;

	ssize_t steps = llabs(dx) > llabs(dy) ? llabs(dx) : llabs(dy);

	float x_inc = dx / (float)steps;
	float y_inc = dy / (float)steps;

	float xf = x;
	float yf = y;
	for (ssize_t i = 0; i <= steps; i++)
	{
		my_pixel_put(img, (ssize_t)roundf(xf), (ssize_t)roundf(yf), color);
		xf += x_inc;
		yf += y_inc;
	}
}

		// if (!(ray->my < 0 || ray->mx < 0 || ray->mx > cube->max_x * MINISQ - 1 || ray->my > cube->max_y * MINISQ - 1))
		// {
		// 	put_star(&(cube->mlx->mini), ray->mx + cube->mlx->mini.border + 1, ray->my + cube->mlx->mini.border, get_color(1, 1, 1));
		// 	put_star(&(cube->mlx->mini), ray->mx + cube->mlx->mini.border, ray->my + cube->mlx->mini.border + 1, get_color(1, 1, 1));
		// 	put_star(&(cube->mlx->mini), ray->mx + cube->mlx->mini.border - 1, ray->my + cube->mlx->mini.border, get_color(1, 1, 1));
		// 	put_star(&(cube->mlx->mini), ray->mx + cube->mlx->mini.border, ray->my + cube->mlx->mini.border - 1, get_color(1, 1, 1));
		// 	my_pixel_put(&(cube->mlx->mini), ray->mx + cube->mlx->mini.border, ray->my + cube->mlx->mini.border, get_color(0, 0, 0));
		// 	//put_star(&(cube->mlx->mini), ray->mx + cube->mlx->mini.border, ray->my + cube->mlx->mini.border, get_color(1, 1, 1));
		// 	printf("3:px:%zu py:%zu ray->r_x:%f ray->r_y:%f rot:%f char:%c \n", ray->mx, ray->my, ray->r_x, ray->r_y, ray->pa, cube->mini_map[ray->my][ray->mx]);
		// 	//put_line(&(cube->mlx->mini), line, get_color(0.1, 0.3, 0.8));
		// }

void	ray_vert(t_ray *ray, t_player *player, t_cubed *cube)
{
	float	a_tan = 1/tan(ray->pa);
	bool	hit = 0;
	bool	down;

	down = 0;
	(void)down;
	if (ray->pa < cube->pie) //up
	{
		ray->r_y = ((ssize_t)(player->p_y / MINISQ) * MINISQ) - 0.0001;
		ray->r_x = (player->p_y - ray->r_y) * a_tan + player->p_x;
		ray->y_offset = - MINISQ;
		ray->x_offset = ray->y_offset * -a_tan;
	}
	else if (ray->pa > cube->pie) //down
	{
		ray->r_y = ((ssize_t)((ssize_t)(player->p_y / MINISQ) * MINISQ)) + MINISQ;
		ray->r_x = (player->p_y - ray->r_y - 0.01) * a_tan + player->p_x;
		ray->y_offset = MINISQ;
		ray->x_offset = ray->y_offset * -a_tan;
		down = 1;
	}
	if (ray->pa == 0.00 || (ray->pa  == cube->pie))
	{
		ray->r_x = player->p_x;
		ray->r_y = player->p_x;
		hit = 1;
	}
	while (hit == 0)
	{
		ray->mx = ray->r_x;
		ray->my = ray->r_y;
		if (ray->my < 1 || ray->mx < 1 || ray->mx > cube->max_x * MINISQ - 1 || ray->my > cube->max_y * MINISQ - 1
			|| !cube->mini_map[ray->my + 1] || cube->mini_map[ray->my + 1][ray->mx] == '1' || cube->mini_map[ray->my - 1][ray->mx] == '1'
			|| cube->mini_map[ray->my][ray->mx + 1] == '1' || cube->mini_map[ray->my][ray->mx - 1] == '1'
			|| cube->mini_map[ray->my][ray->mx] == '1')
			hit = 1;
		else
		{
			ray->r_x += ray->x_offset;
			ray->r_y += ray->y_offset;
		}
	}
	ray->v_x = ray->r_x;
	ray->v_y = ray->r_y;
	ray->dist_v = sqrt((ray->r_x - player->p_x) * (ray->r_x - player->p_x) + (ray->r_y - player->p_y) * (ray->r_y - player->p_y));
}

void	ray_hor(t_ray *ray, t_player *player, t_cubed *cube)
{
	ssize_t	hit;
	bool	left;
	float	n_tan = tan(ray->pa);

	hit = 0;
	left = 0;
	(void)left;
	if (ray->pa < cube->pie / 2 || ray->pa > cube->pie  * 3 / 2) // right
	{
		ray->r_x = ((ssize_t)(player->p_x / MINISQ) * MINISQ) + MINISQ;
		ray->r_y = (player->p_x - ray->r_x) * n_tan + player->p_y;
		ray->x_offset = MINISQ;
		ray->y_offset = (ray->x_offset) * -n_tan;
	}
	else if (ray->pa > cube->pie / 2 && ray->pa < cube->pie * 3 / 2) //left
	{
		ray->r_x = (float)((float)((ssize_t)(player->p_x / MINISQ) * MINISQ) - 0.0001f);
		ray->r_y = floor((player->p_x - ray->r_x) * n_tan - 0.01) + player->p_y;
		ray->x_offset = -MINISQ;
		ray->y_offset = ray->x_offset * -n_tan;
		left = 1;
	}
	else
	{
		ray->r_x = player->p_x;
		ray->r_y = player->p_y;
		hit = 1;
	}
	while (hit == 0)
	{
		ray->mx = floor(ray->r_x);
		ray->my = floor(ray->r_y);
		if (ray->my < 1 || ray->mx < 1 || ray->mx >= cube->max_x * MINISQ - 1 || ray->my >= cube->max_y * MINISQ - 1
			|| !cube->mini_map[ray->my + 1] || cube->mini_map[ray->my + 1][ray->mx] == '1' || cube->mini_map[ray->my - 1][ray->mx] == '1'
			|| cube->mini_map[ray->my][ray->mx + 1] == '1' || cube->mini_map[ray->my][ray->mx - 1] == '1'
			|| cube->mini_map[ray->my][ray->mx] == '1')
			hit = 1;
		else
		{
			ray->r_x += ray->x_offset;
			ray->r_y += ray->y_offset;
		}
		// ray->dist_h = sqrt((ray->r_x - player->p_x) * (ray->r_x - player->p_x) + (ray->r_y - player->p_y) * (ray->r_y - player->p_y));
		// if (ray->dist_h >= ray->dist_v)
		// 	return ;
	}
	ray->dist_h = sqrt((ray->r_x - player->p_x) * (ray->r_x - player->p_x) + (ray->r_y - player->p_y) * (ray->r_y - player->p_y));
}

void	init_ray(t_cubed *cube, t_img *mini, t_ray *ray, t_line *line)
{
	ft_bzero(ray, sizeof(*ray));
	ray->pa = cube->player->rad - 45 * RAY_ANGL;
	line->x = cube->player->p_x + mini->border;
	line->y = cube->player->p_y + mini->border;
	line->len = 0;
	if (ray->pa < 0)
		ray->pa += (2 * cube->pie);
	else if (ray->pa > 2 * cube->pie)
		ray->pa -= (2 * cube->pie);
}

void	put_ray(t_img *game, t_ray *ray)
{
	(void)ray;
	(void)game;
}

void	ray_cal(t_cubed *cube, t_line *line, t_player *player)
{
	t_ray	ray;
	t_img	*mini;
	t_img	*game;

	mini = &cube->mlx->mini;
	init_ray(cube, mini, &ray, line);
	game = &cube->mlx->game;
	for (int i = 0; i < game->width / 2; i++)
	{
		ray_vert(&ray, player, cube);
		ray_hor(&ray, player, cube);
		if (ray.dist_v < ray.dist_h && ray.dist_v != 0)
		{
			ray.r_y = ray.v_y;
			ray.r_x = ray.v_x;
			ray.dist_opt = ray.dist_v;
		}
		else
			ray.dist_opt = ray.dist_h;
		if (ray.pa > cube->pie)
			line->x_end = floorf(ray.r_x) + mini->border;
		else
			line->x_end = roundf(ray.r_x) + mini->border;
		line->y_end = round(ray.r_y) + mini->border;
		line->rot = ray.pa;
		ray.pa += (RAY_ANGL / (((float)(game->width) / 2.0f) / 90.0f));
		if (ray.pa > 2 * cube->pie)
			ray.pa -= (2 * cube->pie);
		//put_ray();
		if (cube->mini && cube->ray)
			put_line(mini, line, get_color(0.1, 0.3, 0.8));
	}
}

void	mini_put_player(t_img *mini, t_player *player)
{
	t_line	line;

	line.x = player->p_x + mini->border;
	line.y = player->p_y + mini->border;
	line.len = 50;
	line.rot = player->rad;
	put_line(mini, &line, get_color(1, 1, 1));
	put_star(mini, player->p_x + mini->border, player->p_y + mini->border, get_color(1, 0, 1));
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
		j = -1;
		while (cube->mini_map[i][++j])
		{
			mini_put_sq(mini, j, i, cube->mini_map[i][j]);
		}
	}
	mini_put_player(mini, cube->player);
}

bool	init_mini_map(t_cubed *cube, t_mlx *mlx)
{
	t_img *mini;

	mini = &mlx->mini;
	mini->border = MINISQ / 5;
	mini->height = cube->max_y * MINISQ + 2 * mini->border;
	mini->width = cube->max_x * MINISQ + 2 * mini->border;
	mini->img = mlx_new_image(mlx->mlx, mini->width, mini->height);
	if (!mini->img)
		return (0);
	mini->addr = mlx_get_data_addr(mini->img, &mini->bits_per_pixel, &mini->line_length, &mini->endian);
	if (!mini->addr)
		return (0);
	set_mini_img(cube, cube->mlx);
	return (1);
}

void	put_image(t_cubed *cube, t_mlx *mlx)
{
	t_line	line;
	ray_cal(cube, &line, cube->player);
	if (cube->mini)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->mini.img, 0, 0);
}

bool	init_game(t_cubed *cube, t_mlx *mlx)
{
	t_img	*game;
	t_line	line;
	
	game = &mlx->game;
	game->border = 0;
	game->height = mlx->y_win;
	game->width = mlx->x_win;
	game->img = mlx_new_image(mlx->mlx, game->width, game->height);
	if (!game->img)
		return (0);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
	if (!game->addr)
		return (0);
	ray_cal(cube, &line, cube->player);
	return (1);
}

bool	init_mlx(t_cubed *cube, t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx_get_screen_size(mlx->mlx, &mlx->x_win, &mlx->y_win);
	if ((float)(mlx->x_win) / (float)(mlx->y_win) > 16.0f / 9.0f)
		mlx->x_win = (float)(mlx->y_win) * 16.0f / 9.0f;
	mlx->win = mlx_new_window(mlx->mlx, mlx->x_win, mlx->y_win, "cub3d");
	mlx_hook(mlx->win, 2, (1L<<0), &mlx_key, cube);
	mlx_hook(mlx->win, 17, 0L, &mlx_exit, cube);
	if (!init_mini_map(cube, mlx))
		return (free_mlx(mlx), ft_putendl_fd("fail mini", 2), 0);
	if (!init_game(cube, mlx))
		return (free_mlx(mlx), ft_putendl_fd("game failed", 2), 0);
	if (!mlx->win)
		return (free_mlx(mlx), 0);
	return (1);
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

int	main(int argc, char **argv)
{
	t_cubed		cube;
	t_mlx		mlx;
	t_player	player;
	char *lines[] = {
	"111111 11111",
    "100001 10001",
    "101111110001",
    "100000000101",
    "100001110101",
    "1000111N0111",
    "100110010111",
    "100111000101",
    "100000000001",
    "111111111111",
    NULL
	};

	(void)argv;
	if (argc != 2)
		return (1);
	ft_bzero(&cube, sizeof(t_cubed));
	ft_bzero(&mlx, sizeof(t_mlx));
	ft_bzero(&player, sizeof(t_player));
	cube.player = &player;
	cube.mlx = &mlx;
	cube.pie = 3.141592653589793;
	if (!ft_strncmp("1", argv[1], 1))
	{
		if (!parsing_map(&cube))
			return (1);
	}
	else
	{
		cube.map = &lines[0];
		cube.max_x = 12;
		cube.max_y = 10;
	}
	if (!mini_map(&cube))
		return (1);
	puts("lmao");
	if (!execute(&cube))
		return (1);
}



