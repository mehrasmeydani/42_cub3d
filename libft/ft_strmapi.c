/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/04/26 15:57:03 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*out;
	ssize_t	i;

	if (!s || !f)
		return (NULL);
	out = (char *)ft_calloc(ft_strlen(s) + 1, 1);
	if (!out)
		return (NULL);
	i = -1;
	while (s[++i])
		out[i] = (*f)(i, s[i]);
	return (out);
}
