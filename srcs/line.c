/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:40:20 by mehras            #+#    #+#             */
/*   Updated: 2025/12/18 23:40:21 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cubed.h"

void	put_line(t_img *img, t_line *line, uint32_t color)
{
	ssize_t x = line->x;
	ssize_t y = line->y;


	if (line->len != 0)
	{
		line->x_end = line->x + roundf(cos(line->rot) * line->len);
		line->y_end = line->y - roundf(sin(line->rot) * line->len);
	}

	ssize_t dx = line->x_end - line->x;
	ssize_t dy = line->y_end - line->y;

	ssize_t steps = llabs(dx) > llabs(dy) ? llabs(dx) : llabs(dy);

	float x_inc = dx / (float)steps;
	float y_inc = dy / (float)steps;

	float xf = x;
	float yf = y;
	for (ssize_t i = 0; i <= steps; i++)
	{
		my_pixel_put(img, (ssize_t)roundf(xf), (ssize_t)roundf(yf), color);
		xf += x_inc;
		yf += y_inc;
	}
}
