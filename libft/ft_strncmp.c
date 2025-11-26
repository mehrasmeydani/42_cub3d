/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/04/26 16:10:57 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	t_uc	*s_1;
	t_uc	*s_2;

	i = 0;
	s_1 = (t_uc *)s1;
	s_2 = (t_uc *)s2;
	if (!n)
		return (0);
	while (s1[i] && s_1[i] == s_2[i] && i < n - 1)
		i++;
	return ((s_1[i] - s_2[i]));
}
