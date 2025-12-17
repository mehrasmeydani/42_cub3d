/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:18:59 by eprottun          #+#    #+#             */
/*   Updated: 2025/12/17 15:19:47 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>

static int	element_found(char *str, int *bitmap)
{
	if (!(*bitmap & (MAP | NO)) && !ft_strncmp("NO ", str, 3))
		*bitmap |= NO;
	else if (!(*bitmap & (MAP | EA)) && !ft_strncmp("EA ", str, 3))
		*bitmap |= EA;
	else if (!(*bitmap & (MAP | SO)) && !ft_strncmp("SO ", str, 3))
		*bitmap |= SO;
	else if (!(*bitmap & (MAP | WE)) && !ft_strncmp("WE ", str, 3))
		*bitmap |= WE;
	else if (!(*bitmap & (MAP | F)) && !ft_strncmp("F ", str, 2))
		*bitmap |= F;
	else if (!(*bitmap & (MAP | C)) && !ft_strncmp("C ", str, 2))
		*bitmap |= C;
	else if (str[count_spaces(str)] == '1')
		*bitmap |= MAP;
	else
		return (0);
	return (1);
}

static int	is_valid_line(char *str, int i, int bitmap)
{
	if (bitmap & MAP)
		return (str[i] == '\n' && (str[i + 1] == '\n' || !str[i + 1]));
	return (str[i] == '\n' || !str[i]);
}

int	find_elements(t_parser *data)
{
	int	iter;
	int	bitmap;

	iter = -1;
	bitmap = 0;
	while (data->full[++iter])
	{
		if (iter != 0 && data->full[iter - 1] != '\n')
			continue ;
		if (!element_found(&data->full[iter], &bitmap)
			&& !is_valid_line(data->full, iter, bitmap))
			return (write(2, "Error\nInvalid elements\n", 24), -1);
	}
	if ((bitmap & 127) != (NO | EA | SO | WE | F | C | MAP))
		return (write(2, "Error\nElements missing\n", 24), -1);
	return (0);
}

int	parser(const char *filename, t_parser *data)
{
	int	info;

	init_data(data);
	if (ft_strlen(filename) < 4
		|| ft_strncmp(".cub", &filename[ft_strlen(filename) - 4], 4))
		return (write(2, "Error\nWrong filename\n", 22), -1);
	if (get_file(filename, data) == -1)
		return (frees(data), -1);
	if (find_elements(data) == -1)
		return (frees(data), -1);
	if (get_map(data) == -1)
		return (frees(data), -1);
	info = 0;
	while (info < 6)
	{
		if (get_info(info, data) == -1)
			return (frees(data), -1);
		info++;
	}
	return (0);
}
