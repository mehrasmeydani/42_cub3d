/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:23:26 by megardes          #+#    #+#             */
/*   Updated: 2026/01/08 12:39:30 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_BONUS_H
# define CUBED_BONUS_H

# include "libft_bonus.h"
# include "parser_bonus.h"
# include <mlx.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <stdint.h>
# include <math.h>
# include <sys/time.h>

# define RED 0xff0000
# define GRN 0x00ff00
# define BLU 0x0000ff
# define MINISQ 64
# define SCALE 4
# ifndef MOVE
#  define MOVE 2
# endif
# define TURN 0.1
# define RAY_ANGL 0.0174533
# define TURN_2 0.035
# define ANGLE 30.0f
# define N 0
# define S 1
# define W 2
# define E 3
# define TEXT_SIZE 2048
# define FORWARD 1
# define BACKWARD -1
# define STOP 0
# define LEFT -1
# define RIGHT 1
# define FPS 16

typedef struct s_putline
{
	ssize_t	dx;
	ssize_t	dy;
	ssize_t	steps;
	float	x_inc;
	float	y_inc;
	float	xf;
	float	yf;
}	t_putline;

typedef struct s_move
{
	int		straight;
	int		side;
	int		turn;
	int		y;
}	t_move;

typedef struct s_ray
{
	float		r_y;
	float		r_x;
	float		x_offset;
	float		y_offset;
	long double	dist_v;
	long double	dist_h;
	float		v_x;
	float		v_y;
	float		pa;
	int			h_face;
	int			v_face;
	int			opt_face;
	float		dist_opt;
	ssize_t		mx;
	ssize_t		my;
	ssize_t		i;
	float		rot;
}	t_ray;

typedef struct s_line
{
	ssize_t	x;
	ssize_t	y;
	ssize_t	x_end;
	ssize_t	y_end;
	float	len;
	float	rot;
}	t_line;

typedef struct s_img
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		border;
}	t_img;

typedef struct s_putray
{
	ssize_t	j;
	ssize_t	offset;
	float	line_len;
	ssize_t	x;
}	t_putray;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*ptr;
	t_img	mini;
	t_img	game;
	t_img	text[4][4];
	int		x_win;
	int		y_win;
	int		frame;
}	t_mlx;

typedef struct s_player
{
	float		rad;
	ssize_t		x_i;
	float		x_f;
	ssize_t		y_i;
	float		y_f;
	ssize_t		p_x;
	ssize_t		p_y;
}	t_player;

typedef struct s_cubed
{
	char		**map;
	char		**mini_map;
	char		*xpm[4][4];
	t_player	*player;
	t_mlx		*mlx;
	t_move		moving;
	ssize_t		max_x;
	ssize_t		max_y;
	uint32_t	floor;
	uint32_t	head;
	float		pie;
	bool		mini;
	bool		ray;
	bool		mouse;
}	t_cubed;

void		set_mini_img(t_cubed *cube, t_mlx *mlx);
void		ft_free(char **in);
ssize_t		is_in(char c, char *str);
bool		mini_map(t_cubed *cube);
void		set_player(t_cubed *cube);
void		put_image(t_cubed *cube, t_mlx *mlx);
void		my_pixel_put(t_img *img, ssize_t x, ssize_t y, uint32_t color);
uint32_t	get_color_xpm(t_img *img, ssize_t x, ssize_t y);
void		put_ray(t_cubed *cube, t_mlx *mlx, t_ray *ray);
uint32_t	get_color(float r, float g, float b);
int			parser(const char *filename, t_parser *data);
int			mouse(int x, int y, void *in);
int			mlx_exit(void *in);
void		free_and_exit(t_cubed *cube, int fd, char *str);
int			mlx_key_press(int key_code, void *in);
int			mlx_key_release(int key_code, void *in);
void		init_mlx(t_cubed *cube, t_mlx *mlx);
void		init_imgs(t_cubed *cube, t_mlx *mlx);
void		ray_cal(t_cubed *cube, t_line *line, t_player *player);
bool		init_game(t_cubed *cube, t_mlx *mlx);
void		move(t_cubed *cube, t_move *moving);
void		put_line(t_img *img, t_line *line, uint32_t color);
void		set_opt(t_ray *ray);
void		init_ray(t_cubed *cube, t_img *mini, t_ray *ray, t_line *line);
void		set_dir_vert(t_ray *ray, t_cubed *cube, t_player *player);
bool		check_ray(t_ray *ray, t_cubed *cube);
void		x_op_util(t_cubed *cube, t_player *player, float cosine, bool i);
void		y_op_util(t_cubed *cube, t_player *player, float sine, bool i);

#endif
