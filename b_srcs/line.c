/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:40:20 by mehras            #+#    #+#             */
/*   Updated: 2026/01/04 16:29:23 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../b_header/cubed.h"

void	put_line(t_img *img, t_line *line, uint32_t color)
{
	t_putline	putline;
	ssize_t		i;

	if (line->len != 0)
	{
		line->x_end = line->x + roundf(cos(line->rot) * line->len);
		line->y_end = line->y - roundf(sin(line->rot) * line->len);
	}
	putline.dx = line->x_end - line->x;
	putline.dy = line->y_end - line->y;
	if (llabs(putline.dx) > llabs(putline.dy))
		putline.steps = llabs(putline.dx);
	else
		putline.steps = llabs(putline.dy);
	putline.x_inc = putline.dx / (float)putline.steps;
	putline.y_inc = putline.dy / (float)putline.steps;
	putline.xf = line->x;
	putline.yf = line->y;
	i = -1;
	while (++i <= putline.steps)
	{
		my_pixel_put(img, roundf(putline.xf), roundf(putline.yf), color);
		putline.xf += putline.x_inc;
		putline.yf += putline.y_inc;
	}
}
