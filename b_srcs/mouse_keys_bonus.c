/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_keys_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:18:05 by mehras            #+#    #+#             */
/*   Updated: 2026/01/04 17:13:14 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed_bonus.h"

int	mlx_key_release(int key_code, void *in)
{
	t_cubed	*cube;

	cube = (t_cubed *)in;
	if ((key_code == XK_W || key_code == XK_w)
		&& cube->moving.straight == FORWARD)
		cube->moving.straight = STOP;
	if ((key_code == XK_S || key_code == XK_s)
		&& cube->moving.straight == BACKWARD)
		cube->moving.straight = STOP;
	if ((key_code == XK_A || key_code == XK_a) && cube->moving.side == RIGHT)
		cube->moving.side = STOP;
	if ((key_code == XK_d || key_code == XK_D) && cube->moving.side == LEFT)
		cube->moving.side = STOP;
	if (key_code == XK_Right && cube->moving.turn == RIGHT)
		cube->moving.turn = STOP;
	if (key_code == XK_Left && cube->moving.turn == LEFT)
		cube->moving.turn = STOP;
	return (0);
}

int	mlx_key_press(int key_code, void *in)
{
	t_cubed	*cube;

	cube = (t_cubed *)in;
	if (key_code == XK_Escape)
		mlx_exit(in);
	if (key_code == XK_W || key_code == XK_w)
		cube->moving.straight = FORWARD;
	if (key_code == XK_S || key_code == XK_s)
		cube->moving.straight = BACKWARD;
	if (key_code == XK_A || key_code == XK_a)
		cube->moving.side = RIGHT;
	if (key_code == XK_d || key_code == XK_D)
		cube->moving.side = LEFT;
	if (key_code == XK_Right)
		cube->moving.turn = RIGHT;
	if (key_code == XK_Left)
		cube->moving.turn = LEFT;
	if (key_code == XK_R || key_code == XK_r)
		cube->ray = !cube->ray;
	if (key_code == XK_Q || key_code == XK_q)
		cube->mini = !cube->mini;
	if (key_code == XK_m || key_code == XK_M)
		cube->mouse = !cube->mouse;
	return (1);
}

void	turn_mouse(t_cubed *cube, t_player *player, bool left)
{
	if (left)
	{
		if (player->rad + TURN_2 > cube->pie * 2)
			player->rad = TURN_2 + player->rad - cube->pie * 2;
		else
			player->rad += TURN_2;
	}
	else
	{
		if (player->rad - TURN_2 < 0)
			player->rad = -TURN_2 + player->rad + cube->pie * 2;
		else
			player->rad -= TURN_2;
	}
}

int	mouse(int x, int y, void *in)
{
	t_cubed	*cube;

	cube = (t_cubed *)in;
	(void)y;
	if (!cube->mouse)
		return (0);
	if (cube->moving.y == -1)
		cube->moving.y = y;
	if (x > cube->moving.y)
		turn_mouse(cube, cube->player, 0);
	else if (x < cube->moving.y)
		turn_mouse(cube, cube->player, 1);
	cube->moving.y = x;
	return (1);
}
