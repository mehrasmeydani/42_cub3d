/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 02:06:36 by mehras            #+#    #+#             */
/*   Updated: 2025/12/19 02:07:52 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

uint32_t	get_color(float r, float g, float b)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	red = (uint8_t)roundf(((RED >> 16) & 0xFF) * r);
	green = (uint8_t)roundf(((GRN >> 8) & 0xFF) * g);
	blue = (uint8_t)roundf((BLU & 0xFF) * b);
	return ((red << 16) | (green << 8) | blue);
}

uint32_t	get_color_xpm(t_img *img, ssize_t x, ssize_t y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(uint32_t *)dst);
}
