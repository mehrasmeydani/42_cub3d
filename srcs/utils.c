/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:41:10 by eprottun          #+#    #+#             */
/*   Updated: 2026/01/04 14:39:41 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"

size_t	count_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == 32)
		i++;
	return (i);
}

int	valid_number(const char *str)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && number / 1000 == 0)
	{
		number *= 10;
		number += str[i] - 48;
		i++;
	}
	if (number > 255)
		return (0);
	else
		return (1);
}

void	init_data(t_parser *data)
{
	size_t	iter;

	data->full = NULL;
	data->file = NULL;
	data->map = NULL;
	iter = 0;
	while (iter < 4)
	{
		data->textures[iter] = NULL;
		iter++;
	}
}

void	free_map(t_parser *data)
{
	int	iter;

	if (data->full)
		free(data->full);
	if (data->file)
	{
		iter = -1;
		while (data->file[++iter])
			free(data->file[iter]);
		free(data->file);
	}
	if (data->map)
	{
		iter = -1;
		while (data->map[++iter])
			free(data->map[iter]);
		free(data->map);
	}
	iter = -1;
	while (++iter < 4 && data->textures[iter])
		free(data->textures[iter]);
}

int	is_valid_line(char *str, int i, int bitmap)
{
	if (bitmap & MAP)
		return (str[i] == '\n' && (str[i + 1] == '\n' || !str[i + 1]));
	return (str[i] == '\n' || !str[i]);
}
