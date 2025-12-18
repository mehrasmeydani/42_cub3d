/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:41:10 by eprottun          #+#    #+#             */
/*   Updated: 2025/12/18 21:11:46 by mehras           ###   ########.fr       */
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
	while (++iter < 4)
		if (data->textures[iter])
			free(data->textures[iter]);
}

int	is_valid_line(char *str, int i, int bitmap)
{
	if (bitmap & MAP)
		return (str[i] == '\n' && (str[i + 1] == '\n' || !str[i + 1]));
	return (str[i] == '\n' || !str[i]);
}
