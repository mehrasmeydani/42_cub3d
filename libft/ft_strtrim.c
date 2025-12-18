/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/08/16 16:58:40 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	is_in(const char *set, char c)
{
	ssize_t	i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*out;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 1;
	while (is_in(set, s1[i]))
		i++;
	while (i != ft_strlen(s1) && is_in(set, s1[ft_strlen(s1) - j]))
		j++;
	j--;
	out = (char *)ft_calloc(ft_strlen(s1) - (j + i) + 1, sizeof(char));
	if (!out)
		return (out);
	ft_strlcpy(out, s1 + i, ft_strlen(s1) - (i + j) + 1);
	return (out);
}
