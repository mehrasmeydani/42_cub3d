#include "../b_header/cubed.h"

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
	cube->player->x_i = x / MINISQ;
	cube->player->x_f = (float)(x % MINISQ) / (float)(MINISQ);
	cube->player->y_i = y / MINISQ;
	cube->player->y_f = (float)(y % MINISQ) / (float)(MINISQ);
}
