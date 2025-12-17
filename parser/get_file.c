/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:45:29 by eprottun          #+#    #+#             */
/*   Updated: 2025/12/17 15:15:44 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	read_loop(int fd, t_parser *data)
{
	int		ret;
	char	line[101];
	char	*tmp;

	data->full = ft_strdup("");
	if (!data->full)
		return (write(2, "Error\nMalloc fail\n", 19), -1);
	while (1)
	{
		ret = read(fd, line, 100);
		if (ret < 0)
			return (write(2, "Error\nRead failed\n", 19), -1);
		if (!ret)
			break ;
		line[ret] = 0;
		tmp = ft_strjoin(data->full, line);
		if (!tmp)
			return (write(2, "Error\nMalloc fail\n", 19), -1);
		free(data->full);
		data->full = tmp;
	}
	return (0);
}

int	get_file(const char *filename, t_parser *data)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (write(2, "Error\nOpen failed\n", 19), -1);
	if (read_loop(fd, data) == -1)
		return (close(fd), -1);
	data->file = ft_split(data->full, '\n');
	if (!data->file)
		return (write(2, "Error\nMalloc fail\n", 19), close(fd), -1);
	return (close(fd), 0);
}
