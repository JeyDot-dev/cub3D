/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:02:16 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/27 18:02:31 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void	draw_square(t_vector origin, t_imgdata img, char c)
{
	int	color;
	int	x;
	int	y;

	if (c == '1')
		color = rgbo_color(180, 65, 158, 0);
	else if (c == '0')
		color = rgbo_color(80, 108, 90, 0);
	x = origin.x * 30 + 50;
	y = origin.y * 30 + 50;
	while (y < (origin.y + 1) * 30 + 50)
	{
		while (x < (origin.x + 1) * 30 + 50)
		{
			draw_pixel(&img, x, y, color);
			x++;
		}
		x = origin.x * 30 + 50;
		y++;
	}
}
