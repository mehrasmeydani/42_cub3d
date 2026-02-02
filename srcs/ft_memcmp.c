/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/08/16 16:58:40 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	t_uc	*tmp1;
	t_uc	*tmp2;

	i = 0;
	if (!n)
		return (0);
	tmp1 = (t_uc *)s1;
	tmp2 = (t_uc *)s2;
	while (i < n - 1 && tmp1[i] == tmp2[i])
		i++;
	return (tmp1[i] - tmp2[i]);
}
