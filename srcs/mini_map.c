/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:40:25 by mehras            #+#    #+#             */
/*   Updated: 2026/01/08 12:36:14 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

ssize_t	is_in(char c, char *str)
{
	ssize_t	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

static char	char_set(t_cubed *cube, char c, ssize_t k, ssize_t l)
{
	t_player	*player;
	float		rot;

	player = cube->player;
	rot = is_in(c, "ENWS");
	if (rot != -1 && l == MINISQ / 2 && k == MINISQ / 2)
		return (player->rad = cube->pie / 2 * rot, c);
	else if (rot != -1)
		return ('0');
	return (c);
}

void	mini_map_helper(t_cubed *cube, ssize_t i, ssize_t k)
{
	ssize_t	l;
	ssize_t	j;

	j = -1;
	while (cube->map[i][++j])
	{
		l = -1;
		while (++l < MINISQ)
		{
			cube->mini_map[i * MINISQ + k][j * MINISQ + l] = char_set(cube,
					cube->map[i][j], k, l);
			if (i * MINISQ + k > 0
				&& j * MINISQ + l > 0
				&& i * MINISQ + k < cube->max_y * MINISQ - 2
				&& j * MINISQ + l < cube->max_x * MINISQ - 2
				&& cube->mini_map[i * MINISQ + k][j * MINISQ + l] == '1')
			{
				cube->mini_map[i * MINISQ + k + 1][j * MINISQ + l] = '1';
				cube->mini_map[i * MINISQ + k][j * MINISQ + l + 1] = '1';
			}
		}
	}
}

void	set_mini_map(t_cubed *cube)
{
	ssize_t	i;
	ssize_t	k;

	i = -1;
	while (++i < cube->max_y)
	{
		k = -1;
		while (++k < MINISQ)
			mini_map_helper(cube, i, k);
	}
}

bool	mini_map(t_cubed *cube)
{
	ssize_t	i;
	ssize_t	k;

	cube->mini_map = (char **)ft_calloc(cube->max_y * MINISQ + 1,
			sizeof(char *));
	if (!cube->mini_map)
		return (free_and_exit(cube, 2, "Malloc failed"), 0);
	i = -1;
	while (++i < cube->max_y)
	{
		k = -1;
		while (++k < MINISQ)
		{
			cube->mini_map[i * MINISQ + k] = ft_calloc(cube->max_x
					* MINISQ + 1, sizeof(char));
			if (!cube->mini_map[i * MINISQ + k])
				return (free_and_exit(cube, 2, "Malloc failed"), 0);
		}
	}
	set_mini_map(cube);
	return (1);
}
