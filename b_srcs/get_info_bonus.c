/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:38:56 by eprottun          #+#    #+#             */
/*   Updated: 2026/02/02 17:53:39 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed_bonus.h"
#include <stddef.h>

int	extract_path(char *line, int dir, t_parser *data)
{
	size_t	i;
	char	**in;

	i = -1;
	line += 3;
	in = ft_split(line, ' ');
	if (!in)
		return (ft_putendl_fd("Error\nMalloc failed", 2), -1);
	while (in[++i])
		;
	if (i != 4)
		return (ft_free(in),
			ft_putendl_fd("Error\nTexture format wrong", 2), -1);
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
	size_t		line;
	size_t		iter;

	line = 0;
	while (data->file[line])
	{
		iter = count_spaces(data->file[line]);
		if (info < 4 && !ft_strncmp(&data->file[line][iter], arr[info], 3))
		{
			if (extract_path(&data->file[line][iter], info, data) == -1)
				return (-1);
			return (0);
		}
		if (info >= 4 && !ft_strncmp(&data->file[line][iter], arr[info], 2))
		{
			if (extract_color(&data->file[line][iter], info % 4, data) == -1)
				return (ft_putendl_fd("Error\nColor format wrong", 2), -1);
			return (0);
		}
		line++;
	}
	return (0);
}
