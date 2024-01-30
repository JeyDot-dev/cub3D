/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:49:21 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/30 18:39:50 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_ground(t_imgdata *img, int col, int pitch)
{
	int		i;
	int		j;
	char	*tmp;
	int		rgb[3];

	i = (WIN_WIDTH * GAME_HEIGHT) / 2 + WIN_WIDTH * pitch;
	rgb[0] = r_value(col);
	rgb[1] = g_value(col);
	rgb[2] = b_value(col);
	j = -((rgb[0] + rgb[1] + rgb[2]) / 3);
	while (i < WIN_WIDTH * GAME_HEIGHT)
	{
		if (j < 30 && i % (WIN_WIDTH * GAME_HEIGHT / WIN_WIDTH * 7) == 0)
			j += 1;
		tmp = img->addr + (img->bpp / 8) * i;
		*(unsigned int *) tmp = rgbo_color(rgb[0] + j,
				rgb[1] + j, rgb[2] + j, 0);
		i++;
	}
}

void	background(t_imgdata *img, int ground, int sky, int pitch)
{
	int			i;
	int			j;
	char		*tmp;
	int			rgb[3];

	i = 0;
	rgb[0] = r_value(sky);
	rgb[1] = g_value(sky);
	rgb[2] = b_value(sky);
	j = 10;
	while (i <= WIN_WIDTH * GAME_HEIGHT / 2 + WIN_WIDTH * pitch)
	{
		if (j > -20 && i % (WIN_WIDTH * GAME_HEIGHT / WIN_WIDTH * 10) == 0)
			j -= 1;
		tmp = img->addr + (img->bpp / 8) * i;
			*(unsigned int *) tmp = rgbo_color(rgb[0] + j,
				rgb[1] + j, rgb[2] + j, 0);
		i++;
	}
	draw_ground(img, ground, pitch);
}
