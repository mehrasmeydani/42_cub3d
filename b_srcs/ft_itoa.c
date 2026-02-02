/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/08/16 16:58:40 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static void	ft_putnbr(int nb, char *out)
{
	if (nb == -2147483648)
		ft_strlcat(out, "-2147483648", 12);
	else if (nb < 0)
	{
		ft_strlcat(out, "-", 2);
		nb = -nb;
		ft_putnbr(nb, out);
	}
	else if (nb >= 10)
	{
		ft_putnbr(nb / 10, out);
		ft_putnbr(nb % 10, out);
	}
	else
		ft_strlcat(out, &"0123456789"[nb], ft_strlen(out) + 2);
}

char	*ft_itoa(int n)
{
	int		i;
	int		nb;
	char	*out;

	i = 0;
	nb = n;
	if (n <= 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	out = (char *)ft_calloc(i + 1, sizeof(char));
	if (!out)
		return (NULL);
	ft_putnbr(nb, out);
	return (out);
}
