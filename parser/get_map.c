/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:59:14 by eprottun          #+#    #+#             */
/*   Updated: 2025/12/17 15:14:39 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stddef.h>

void	get_map_info(t_parser *data)
{
	size_t	line_iter;
	size_t	iter;

	data->map_pos = -1;
	data->max_x = -1;
	line_iter = 0;
	while (data->file[line_iter])
	{
		iter = 0;
		if (data->map_pos > 0 || ft_strchr("01", data->file[line_iter]
				[count_spaces(data->file[line_iter])]))
		{
			if (data->map_pos == -1)
				data->map_pos = line_iter;
			while (data->file[line_iter][iter])
				iter++;
			if (data->max_x < (int)iter)
				data->max_x = iter;
		}
		line_iter++;
	}
	if (data->map_pos != -1)
		data->max_y = line_iter - data->map_pos;
}

int	create_map(t_parser *data)
{
	int	y;
	int	x;
	int	line_len;

	data->map = ft_calloc((data->max_y + 1), sizeof(char *));
	if (!data->map)
		return (write(2, "Error\nMalloc fail\n", 19), -1);
	y = -1;
	while (++y < data->max_y)
	{
		data->map[y] = ft_calloc(sizeof(char), data->max_x + 1);
		if (!data->map[y])
			return (write(2, "Error\nMalloc fail\n", 19), -1);
		line_len = ft_strlen(data->file[data->map_pos + y]);
		x = -1;
		while (++x < data->max_x)
		{
			data->map[y][x] = ' ';
			if (x < line_len)
				data->map[y][x] = data->file[data->map_pos + y][x];
		}
	}
	return (0);
}

int	validate_cell(t_parser *data, size_t y, size_t x, int *player_found)
{
	const int	offset[3] = {-1, 1, 0};
	int			runs;

	if (ft_strchr("NEWS", data->map[y][x]) && ++(*player_found) > 1)
		return (write(2, "Error\nMore than one player\n", 28), -1);
	if (!ft_strchr("NEWS01 ", data->map[y][x]))
		return (write(2, "Error\nWrong character found\n", 29), -1);
	if (!ft_strchr("1 ", data->map[y][x]))
	{
		if ((int)x == data->max_x - 1 || (int)y == data->max_y - 1 || !x || !y)
			return (write(2, "Error\nWalls missing\n", 21), -1);
		runs = -1;
		while (++runs < 8)
			if (data->map[y + offset[runs / 3]][x + offset[runs % 3]] == ' ')
				return (write(2, "Error\nWalls missing\n", 21), -1);
	}
	return (0);
}

int	check_map(t_parser *data)
{
	size_t	y_iter;
	size_t	x_iter;
	int		player_found;

	y_iter = 0;
	player_found = 0;
	while (data->map[y_iter])
	{
		x_iter = 0;
		while (data->map[y_iter][x_iter])
		{
			if (validate_cell(data, y_iter, x_iter, &player_found) == -1)
				return (-1);
			x_iter++;
		}
		y_iter++;
	}
	if (player_found == 0)
		return (write(2, "Error\nNo player\n", 17), -1);
	return (0);
}

int	get_map(t_parser *data)
{
	get_map_info(data);
	if (create_map(data) == -1)
		return (-1);
	if (check_map(data) == -1)
		return (-1);
	return (0);
}
