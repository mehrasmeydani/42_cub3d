/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:48:24 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:48:25 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static void	ft_swap(char **a, char **b)
{
	char	*why;

	why = *a;
	*a = *b;
	*b = why;
}

void	ft_sort_string_tab(char **tab)
{
	ssize_t		i;
	ssize_t		j;

	i = -1;
	while (tab[++i] && tab[i + 1])
	{
		j = i;
		while (tab[++j])
			if (0 < ft_strcmp(tab[i], tab[j]))
				ft_swap(&tab[i], &tab[j]);
	}
}
