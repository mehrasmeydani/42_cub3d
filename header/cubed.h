/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:23:26 by megardes          #+#    #+#             */
/*   Updated: 2025/11/30 19:25:16 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CUBED_H
# define CUBED_H

# include "../libft/libft.h"
# include <mlx.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <stdio.h> // testing
# include <stdint.h>
# include <math.h>


# define RED 0xff0000
# define GRN 0x00ff00
# define BLU 0x0000ff
# define MINISQ 64
// # define PIE 3.141592653589793
// # define TURN	0.0348994967
# ifndef MOVE
#  define MOVE 10
# endif
# define TURN 0.17364817766
# define RAY_ANGL 0.03
# define RAY_NUMBER 25

typedef	struct s_line
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
} t_img;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*ptr;
	t_img		mini;
	int			x_win;
	int			y_win;
}	t_mlx;


typedef struct	s_player
{
	float		rad;
	ssize_t		x_i;
	float		x_f;
	ssize_t		y_i;
	float		y_f;
	ssize_t		p_x;
	ssize_t		p_y;
}	t_player;

typedef struct	s_cubed
{
	char		**map;
	char		**mini_map;
	t_player	*player;
	t_mlx		*mlx;
	ssize_t		max_x;
	ssize_t		max_y;
}	t_cubed;

void	set_mini_img(t_cubed *cube, t_mlx *mlx);

#endif

