/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/08/16 16:58:40 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static ssize_t	count(const char *str, char c)
{
	size_t	j;
	ssize_t	i;

	j = 0;
	i = 0;
	while (str[j])
	{
		while (str[j] && (str[j] == c))
			j++;
		if (str[j] && !(str[j] == c))
			i++;
		while (str[j] && !(str[j] == c))
			j++;
	}
	return (i);
}

static char	**ft_free(char **in, ssize_t i)
{
	ssize_t	j;

	j = -1;
	while (++j < i)
		free(in[j]);
	free(in);
	return (NULL);
}

static char	*str(char *s, char c)
{
	size_t	i;
	char	*out;

	i = 0;
	while (s[i] && s[i] != c && ++i)
		;
	out = ft_substr(s, 0, i);
	if (!out)
		return (NULL);
	return (out);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	char	*tmp;
	ssize_t	i;

	i = -1;
	if (!s)
		return (NULL);
	out = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	tmp = (char *)s;
	while (++i < count(s, c))
	{
		while (*tmp && *tmp == c)
			tmp++;
		out[i] = str(tmp, c);
		if (!out[i])
			return (ft_free(out, i));
		while (*tmp && *tmp != c)
			tmp++;
	}
	out[i] = NULL;
	return (out);
}
