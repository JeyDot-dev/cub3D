/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:49:21 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/05 16:06:28 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void draw_ground(t_imgdata *img, int col, int pitch)
{
	int			i;
	int			j;
	char	*tmp;
	int		rgb[3];

	i = (WIN_WIDTH * GAME_HEIGHT) / 2 + WIN_WIDTH * pitch; //TODO : change 0 to ground height (pitch)
	j = -30;
	rgb[0] = r_value(col);
	rgb[1] = g_value(col);
	rgb[2] = b_value(col);
	while (i < WIN_WIDTH * GAME_HEIGHT)
	{
		if (i % (WIN_WIDTH * GAME_HEIGHT / WIN_WIDTH * 10) == 0)
			j += 1;
		tmp = img->addr + (img->bpp / 8) * i;
		*(unsigned int *) tmp = rgbo_color(rgb[0] + j, rgb[1] + j, rgb[2] + j, 0);
		i++;
	}
}

void background(t_imgdata *img, int ground, int sky, int pitch)
{
	int			i;
	int			j;
	char		*tmp;
	int			rgb[3];

	i = 0;
	j = 0;
	rgb[0] = r_value(sky);
	rgb[1] = g_value(sky);
	rgb[2] = b_value(sky);
	while (i <= WIN_WIDTH * GAME_HEIGHT / 2 + WIN_WIDTH * pitch) //TODO : change 0 to ground height (pitch)
	{
		if (i % (WIN_WIDTH * GAME_HEIGHT / WIN_WIDTH * 10) == 0)
			j += 1;
		tmp = img->addr + (img->bpp / 8) * i;
			*(unsigned int *) tmp = rgbo_color(rgb[0] - j, rgb[1] - j, rgb[2] - j, 0);
		i++;
	}
	draw_ground(img, ground, pitch);
}
/*void background(t_imgdata *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < GAME_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			draw_pixel(img, j, i, 0x000000);
			j++;
		}
		i++;
	}
}*/
