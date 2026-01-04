/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:14:09 by eprottun          #+#    #+#             */
/*   Updated: 2026/01/04 14:36:56 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define NO 64
# define EA 32
# define SO 16
# define WE 8
# define F 4
# define C 2
# define MAP 1
# define MEMFAIL 4
# define ERROR 5

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <stddef.h>
# include "libft.h"
# include <limits.h>

typedef struct s_parser
{
	char		*full;
	char		**file;
	int			map_pos;
	int			max_x;
	int			max_y;
	char		*textures[4];
	int			floor[3];
	int			ceiling[3];
	char		**map;
}	t_parser;

int		valid_number(const char *str);
size_t	count_spaces(char *str);
int		get_map(t_parser *data);
int		get_info(int info, t_parser *data);
int		get_file(const char *filename, t_parser *data);
int		parser(const char *filename, t_parser *data);
void	free_map(t_parser *data);
void	init_data(t_parser *data);
int		is_valid_line(char *str, int i, int bitmap);

#endif
