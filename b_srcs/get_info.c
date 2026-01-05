/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:38:56 by eprottun          #+#    #+#             */
/*   Updated: 2026/01/04 20:41:26 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed.h"
#include <stddef.h>

int	extract_path(char *line, int dir, t_parser *data)
{
	size_t	i;
	char	**in;

	i = -1;
	line += 3;
	in = ft_split(line, ' ');
	if (!in)
		return (-1);
	while (in[++i])
		;
	if (i != 4)
		return (ft_free(in), -1);
	i = -1;
	while (++i < 4)
		data->textures[dir][i] = in[i];
	free(in);
	return (0);
}

int	extract_color(char *line, int spec, t_parser *data)
{
	size_t	iter;
	int		*array;
	int		rounds;

	array = data->ceiling;
	if (spec == 0)
		array = data->floor;
	rounds = 0;
	iter = 1;
	while (rounds < 3)
	{
		iter += count_spaces(&line[iter]);
		if (!ft_isdigit(line[iter]))
			return (-1);
		if (!valid_number(&line[iter]))
			return (-1);
		array[rounds] = ft_atoi(&line[iter]);
		while (ft_isdigit(line[iter]))
			iter++;
		iter += count_spaces(&line[iter]);
		if (rounds++ != 2 && line[iter++] != ',')
			return (-1);
	}
	return ((line[iter] != 0) * -1);
}

int	get_info(int info, t_parser *data)
{
	const char	*arr[6] = {"NO ", "EA ", "SO ", "WE ", "F ", "C "};
	size_t		iter;

	iter = 0;
	while (data->file[iter])
	{
		if (info < 4 && !ft_strncmp(data->file[iter], arr[info], 3))
		{
			if (extract_path(data->file[iter], info, data) == -1)
				return (-1);
			return (0);
		}
		if (info >= 4 && !ft_strncmp(data->file[iter], arr[info], 2))
		{
			if (extract_color(data->file[iter], info % 4, data) == -1)
				return (ft_putendl_fd("Error\nElement format wrong", 2), -1);
			return (0);
		}
		iter++;
	}
	return (0);
}
