/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/04/26 16:09:53 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	ssize_t	i;
	char	*tmp;

	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return (tmp = (char *)(s + i), tmp);
	if (s[i] == (char)c)
		return (tmp = (char *)(s + i), tmp);
	return (NULL);
}
