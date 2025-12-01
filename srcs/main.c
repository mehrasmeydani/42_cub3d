/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:21:56 by megardes          #+#    #+#             */
/*   Updated: 2025/12/01 01:23:34 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

float	PIE = 3.141592653589793; 

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
			cube->map[i] = ft_strdup("1000001");
			if (!cube->map[i])
				return (ft_free(cube->map), 0);
		}
		else if (i == j - 3)
		{
			cube->map[i] = ft_strdup("1N00011");
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
	cube->max_y = 9;
	cube->max_x = ft_strlen(cube->map[0]);
	return (1);
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
	if (player->y_f - sine > 1)
	{
		if (cube->map[player->y_i + 1][player->x_i] != '1')
		{
			player->y_i++;
			player->y_f = player->y_f - 1 - sine;
		}
		else
			player->y_f = 0.999;
	}
	else if (player->y_f - sine < 0)
	{
		if (cube->map[player->y_i - 1][player->x_i] != '1')
		{
			player->y_i--;
			player->y_f = player->y_f + 1 - sine;
		}
		else
			player->y_f = 0.001;
	}
	else
		player->y_f -= sine;
	player->p_y = (ssize_t)(((double)(player->y_i) + player->y_f) * 64);
}

void	x_op(t_cubed *cube, t_player *player, float cosine)
{
	if (player->x_f + cosine > 1)
	{
		if (cube->map[player->y_i][player->x_i + 1] != '1')
		{
			player->x_i++;
			player->x_f = player->x_f - 1 + cosine;
		}
		else
			player->x_f = 0.999;
	}
	else if (player->x_f + cosine < 0)
	{
		if (cube->map[player->y_i][player->x_i - 1] != '1')
		{
			player->x_i--;
			player->x_f = player->x_f + 1 + cosine;
		}
		else
			player->x_f = 0.001;
	}
	else
		player->x_f += cosine;
	player->p_x = (ssize_t)round(((double)(player->x_i) + player->x_f) * 64);
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

	printf("x%zu y%zu x%f y%f py%zu px%zu rot%f\n", cube->player->x_i, cube->player->y_i, cube->player->x_f, cube->player->y_f, cube->player->p_y, cube->player->p_x, cube->player->rad);
}

void turn(t_player *player, bool left)
{
	if (left)
	{
		if (player->rad + TURN > PIE * 2)
			player->rad = TURN + player->rad - PIE * 2;
		else
			player->rad += TURN;
	}
	else
	{	
		if (player->rad - TURN < 0)
			player->rad = -TURN + player->rad + PIE * 2;
		else
			player->rad -= TURN;
	}
}

int	mlx_key(int key_code, void *in)
{
	t_cubed *cube;

	cube = (t_cubed *)in;
	if (key_code == XK_Escape)
		mlx_exit(in);
	if (key_code == XK_W || key_code == XK_w)
		move(cube, 1);
	if (key_code == XK_S || key_code == XK_s)
		move(cube, 0);
	if (key_code == XK_A || key_code == XK_a)
		turn(cube->player, 1);
	if (key_code == XK_d || key_code == XK_D)
		turn(cube->player, 0);
	set_mini_img(cube, cube->mlx);
	return (1);
}

ssize_t is_in(char c, char *str)
{
	ssize_t i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
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

void	put_line(t_img *img, t_line *line)
{
	ssize_t x = line->x;
	ssize_t y = line->y;


	if (line->len != 0)
	{
		line->x_end = line->x + roundf(cos(line->rot) * line->len);
		line->y_end = line->y - roundf(sin(line->rot) * line->len);
		//puts("yo");
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
		//printf("xf:%zu yf:%zu\n", (ssize_t)roundf(xf), (ssize_t)roundf(yf));
		put_star_small(img, (ssize_t)roundf(xf), (ssize_t)roundf(yf), get_color(1, 0, 0));
		xf += x_inc;
		yf += y_inc;
	} // fix
}
//
// float	ray_len (t_cubed *cube, t_line *line, t_player *player)
// {
// 	double	x_dir;
// 	double	y_dir;
// 	double	x_at_y;
// 	double	y_at_x;
// 	double	x_d;
// 	double	y_d;
//
// 	x_dir = cosf(line->rot);
// 	y_dir = sinf(line->rot) * -1;
// 	y_d = 0.0;
// 	x_d = 0.0;
// 	if (x_dir && x_dir > 0)
// 	{
// 		while(cube->map[player->y_i + (ssize_t)round(x_d * y_dir)][player->x_i + (ssize_t)x_d + 1] != '1')
// 			x_d++;
// 		x_d += 1.0f - player->x_f;
// 	}
// 	else if (x_dir)
// 	{
// 		while(cube->map[player->y_i + (ssize_t)floor(x_d * y_dir)][player->x_i + (ssize_t)x_d - 1] != '1')
// 			x_d--;
// 		x_d += player->x_f;
// 	}
// 	y_at_x = x_d * tan(line->rot);
// 	printf("x_d:%f\ty_at_x:%f\tsqrt:%f\n", x_d, y_at_x, sqrt((double)y_at_x * (double)y_at_x + (double)x_d * (double)x_d));
// 	if (y_dir && y_dir > 0)
// 	{
// 		while(cube->map[player->y_i + (ssize_t)y_d + 1][player->x_i + (ssize_t)floor((y_d * x_dir))] != '1')
// 			y_d++;
// 		y_d += 1.0f - player->y_f;
// 	}
// 	else if (y_dir)
// 	{
// 		while(cube->map[player->y_i + (ssize_t)y_d - 1][player->x_i + (ssize_t)round(y_d * x_dir)] != '1')
// 			y_d--;
// 		y_d += player->y_f;
// 	}
// 	x_at_y = y_d / tan(line->rot);
// 	printf("y_d:%f\tx_at_y:%f\tsqrt:%f\n", y_d, x_at_y, sqrt((double)x_at_y * (double)x_at_y + (double)y_d * (double)y_d));
// 	if (x_at_y * x_at_y + y_d * y_d < y_at_x * y_at_x + x_d * x_d)
// 		return (sqrt((double)x_at_y * (double)x_at_y + (double)y_d * (double)y_d) * MINISQ);
// 	return (sqrt((double)y_at_x * (double)y_at_x + (double)x_d * (double)x_d) * MINISQ);
// }

float	ray_len (t_cubed *cube, t_line *line, t_player *player)
{
	(void)cube;
	(void)player;
	float	r_y;
	float	r_x;
	float	x_offset;
	float	y_offset;
	float	a_tan = 1/tan(line->rot);
	//double	x_delt;
	//double	y_delt;
	ssize_t	dof = 0;
	int	mx;
	int	my;
	//printf("%f", a_tan);
	(void)a_tan;
	if (line->rot < PIE)
	{
		r_y = ((ssize_t)(player->p_y / 64) * 64) - 0.0001;
		r_x = (player->p_y - r_y) * a_tan + player->p_x;
		y_offset = - MINISQ;
		x_offset = y_offset * -a_tan;
	}
	else if (line->rot > PIE)
	{
		r_y = ((ssize_t)(player->p_y>>6)<<6) + MINISQ;
		r_x = (player->p_y - r_y) * a_tan + player->p_x;
		y_offset = MINISQ;
		x_offset = y_offset * -a_tan;
	}
	else //(line->rot == 0.00 || (line->rot  == PIE))
	{
		r_x = line->x;
		r_y = line->y;
		dof = sqrt(MINISQ);
		puts("lmao2");
		return (250);
	}
	while (dof < sqrt(MINISQ))
	{
		mx = round(r_x);
		my = floor(r_y);
		if (cube->mini_map[my][mx] == '1')
		{
			dof = 8;
		}
		else
		{
			dof +=1;
			r_x += x_offset;
			r_y += y_offset;
		}
	}
	line->len = 0;
	if (line->rot > PIE)
		line->x_end = floorf(r_x) + cube->mlx->mini.border;
	else
		line->x_end = roundf(r_x) + cube->mlx->mini.border;
	line->y_end = floor(r_y) + cube->mlx->mini.border;
	line->rot = player->rad;
	//printf("px:%zu py:%zu r_y:%f r_x:%f rot:%f\n", player->p_x, player->p_y, r_y, r_x, player->rad);
	put_line(&(cube->mlx->mini), line);
	//my_pixel_put(&(cube->mlx->mini), cube->mlx->mini.border + floor(r_x), cube->mlx->mini.border + floor(r_y), get_color(1, 1, 1));
	return (50);
	//return (sqrt(x_delt * x_delt + y_delt * y_delt));
}

void	put_rays(t_cubed *cube, t_img *img, t_line *line)
{
	t_line	ray;
	ssize_t	i;

	i = RAY_NUMBER * -1;
	ray.x = line->x;
	ray.y = line->y;
	(void)cube;
	while (++i < RAY_NUMBER)
	{
		if (line->rot + i * RAY_ANGL > 2 * PIE)
			ray.rot = line->rot + i * RAY_ANGL - 2 * PIE;
		else if (line->rot + i * RAY_ANGL < 0)
			ray.rot = line->rot + i * RAY_ANGL + 2 * PIE;
		else
			ray.rot = line->rot + i * RAY_ANGL;
		ray.len = 50;// = cast_ray(cube->map, cube->max_x, cube->max_y, ray.x, ray.y, ray.rot);
		put_line (img, &ray);
	}
}

void	mini_put_player(t_cubed *cube, t_img *mini, t_player *player)
{
	ssize_t i;
	ssize_t j;
	t_line	line;

	i = mini->border + player->p_x;
	j = mini->border + player->p_y;
	put_star(mini, i, j, get_color(0, 0, 1));
	line.x = i;
	line.y = j;
	line.rot = player->rad;
	(void)cube;
	line.len = 50; //ray_len(cube, &line, cube->player);
	// line.len = cast_ray(cube, player, line.rot);
	//printf("float:%f\t***rad:%f\t***\n", line.len, line.rot /PIE);
	put_line(mini, &line);
	ray_len(cube, &line, player);
	//put_rays(cube, mini, &line);
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
	mini_put_player(cube, mini, cube->player);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mini->img, 0, 0);
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

bool	init_mlx(t_cubed *cube, t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx_get_screen_size(mlx->mlx, &mlx->x_win, &mlx->y_win);
	mlx->win = mlx_new_window(mlx->mlx, mlx->x_win, mlx->y_win, "cub3d");
	if (!init_mini_map(cube, mlx))
		return (ft_putendl_fd("fail mini", 2), 0);
	mlx_hook(mlx->win, 2, (1L<<0), &mlx_key, cube);
	mlx_hook(mlx->win, 17, 0L, &mlx_exit, cube);
	if (!mlx->win)
		return (free_mlx(mlx), 0);
	return (1);
}


void	set_player(t_cubed *cube)
{
	ssize_t	y;
	ssize_t	x;
	ssize_t	rot;
	bool	stop;

	stop = 1;
	y = -1;
	x = 0;
	while (stop && cube->mini_map[++y])
	{
		x = -1;
		while (stop && cube->mini_map[y][++x])
		{
			rot = is_in(cube->mini_map[y][x], "ENWS"); 
			if (rot != -1)
				stop = 0;
		}
	}
	cube->player->p_x = x;
	cube->player->p_y = y;
	printf("%zu %zu\n", x, y);
	cube->player->x_i = x / MINISQ;
	cube->player->x_f = (double)(x % MINISQ) / (double)(MINISQ);
	// cube->player->x_f = 0.5;
	cube->player->y_i = y / MINISQ;
	cube->player->y_f = (double)(y % MINISQ) / (double)(MINISQ);
	//cube->player->rad += 0.5;
	// printf("x%zu y%zu x%f y%f\n", cube->player->x_i, cube->player->y_i, cube->player->x_f, cube->player->y_f);
	// cube->player->y_f = 0.5;
	//cube->player->rad = PIE / 2 * rot; 
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

char	char_set(t_player *player, char c, ssize_t k, ssize_t l)
{
	float	rot;

	rot = is_in(c, "ENWS");
	if (rot != -1 && l == MINISQ / 2 && k == MINISQ / 2)
		return (player->rad = PIE / 2 * rot, c);
	else if (rot != -1)
		return ('0');
	return (c);
}

bool	mini_map(t_cubed *cube)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	k;
	ssize_t	l;

	cube->mini_map = (char **)ft_calloc(cube->max_y * MINISQ + 1, sizeof(char *));
	if (!cube->mini_map)
		return (ft_free(cube->map), 0);
	i = -1;
	while (++i < cube->max_y)
	{
		k = -1;
		while (++k < MINISQ)
		{
			j = -1;
			cube->mini_map[i * MINISQ + k] = (char *)ft_calloc(ft_strlen(cube->map[i]) * MINISQ + 1, sizeof(char));
			if (!cube->mini_map[i * MINISQ + k])
				return (ft_free(cube->mini_map), ft_free(cube->map), 0);
			while (cube->map[i][++j])
			{
				l = -1;
				while (++l < MINISQ)
					cube->mini_map[i * MINISQ + k][j * MINISQ + l] = char_set(cube->player, cube->map[i][j], k, l);
			}
		}
	}
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
	// for (int i = 0; cube.mini_map[i]; i++)
	// {
	// 	ft_putendl_fd(cube.mini_map[i], 1);
	// }
	puts("lmao");
	if (!execute(&cube))
		return (1);
}



