/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/08/16 16:58:40 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strdup(const char *s)
{
	char	*out;

	if (!s)
		return (NULL);
	out = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!out)
		return (NULL);
	ft_strlcpy(out, s, ft_strlen(s) + 1);
	return (out);
}
