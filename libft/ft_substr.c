/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/04/23 12:00:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*out;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len * ft_strlen(s) == 0)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (len + start > ft_strlen(s))
		out = (char *)ft_calloc((ft_strlen(s) - start + 1), sizeof(char));
	else
		out = (char *)ft_calloc((len + 1), sizeof(char));
	if (!out)
		return (NULL);
	if (len > ft_strlen(s))
		ft_strlcpy(out, s + start, ft_strlen(s) + 1);
	else
		ft_strlcpy(out, s + start, len + 1);
	return (out);
}
