/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:23:26 by megardes          #+#    #+#             */
/*   Updated: 2025/11/28 07:29:33 by mehras           ###   ########.fr       */
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


# define RED 	0xff0000
# define GRN 	0x00ff00
# define BLU 	0x0000ff
# define MINISQ 75
# define PIE	3.141592653589793

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
	float	rad;
	ssize_t	x_i;
	float	x_f;
	ssize_t	y_i;
	float	y_f;
}	t_player;

typedef struct	s_cubed
{
	char		**map;
	t_player	*player;
	t_mlx		*mlx;
	ssize_t		max_x;
	ssize_t		max_y;
}	t_cubed;

void	set_mini_img(t_cubed *cube, t_mlx *mlx);

#endif

