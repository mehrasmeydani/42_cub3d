/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:45:29 by eprottun          #+#    #+#             */
/*   Updated: 2025/12/18 19:31:58 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"

int	read_loop(int fd, t_parser *data)
{
	int		ret;
	char	line[101];
	char	*tmp;

	data->full = ft_strdup("");
	if (!data->full)
		return (ft_putendl_fd("Error\nMalloc fail", 2), -1);
	while (1)
	{
		ret = read(fd, line, 100);
		if (ret < 0)
			return (ft_putendl_fd("Error\nRead failed", 2), -1);
		if (!ret)
			break ;
		line[ret] = 0;
		tmp = ft_strjoin(data->full, line);
		if (!tmp)
			return (ft_putendl_fd("Error\nMalloc fail", 2), -1);
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
		return (ft_putendl_fd("Error\nOpen failed", 2), -1);
	if (read_loop(fd, data) == -1)
		return (close(fd), -1);
	data->file = ft_split(data->full, '\n');
	if (!data->file)
		return (ft_putendl_fd("Error\nMalloc fail", 2), close(fd), -1);
	return (close(fd), 0);
}
