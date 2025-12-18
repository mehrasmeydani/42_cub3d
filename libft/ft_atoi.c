/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/08/16 16:58:40 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_atoi(const char *nptr)
{
	int		out;
	ssize_t	j;
	int		sign;

	if (!nptr)
		return (0);
	out = 0;
	j = -1;
	sign = 1;
	while (nptr[++j] == 32 || (nptr[j] >= 9 && nptr[j] <= 13))
		;
	if ((nptr[j] == '-' || nptr[j] == '+') && ++j)
		if (nptr[j - 1] == '-')
			sign = -1;
	while (nptr[j] >= '0' && nptr[j] <= '9')
		out = out * 10 + nptr[j++] - '0';
	return (out * sign);
}
