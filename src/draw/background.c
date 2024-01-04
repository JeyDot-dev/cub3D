/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:49:21 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/04 18:15:09 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void ground(t_imgdata *img, int col)
{
	int			i;
	int			j;
	char		*tmp;

	i = (WIN_WIDTH * GAME_HEIGHT) / 2;
	j = 0;
	while (i < WIN_WIDTH * GAME_HEIGHT)
	{
		if (i % (WIN_WIDTH * GAME_HEIGHT / WIN_WIDTH * 30) == 0)
			j += 3;
		tmp = img->addr + (img->bpp / 8) * i;
		if (col == 1)
			*(unsigned int *) tmp = rgbo_color(20 + j, 0 + j, 40 + j, 0);
		else if (col == 2)
			*(unsigned int *) tmp = rgbo_color(14 + j, 80 - j, 14 - j, 0);
		else if (col == 3)
			*(unsigned int *) tmp = rgbo_color(30 - j, 25 - j, 5 + j, 0);
		else
			*(unsigned int *) tmp = rgbo_color(40, 60, 60, 0);
		i++;
	}
}
void background(t_imgdata *img, int col)
{
	int			i;
	int			j;
	char		*tmp;

	i = 0;
	j = 0;
	while (i <= (WIN_WIDTH * GAME_HEIGHT) / 2)
	{
		if (i % (WIN_WIDTH * GAME_HEIGHT / WIN_WIDTH * 60) == 0)
			j += 2;
		tmp = img->addr + (img->bpp / 8) * i;
		if (col == 1)
			*(unsigned int *) tmp = rgbo_color(0 + j, 90 + j, 130 + j, 0);
		else if (col == 2)
			*(unsigned int *) tmp = rgbo_color(120 + j, 40 - j, 140 - j, 0);
		else if (col == 3)
			*(unsigned int *) tmp = rgbo_color(200 - j, 100 - j, 20 + j, 0);
		else
			*(unsigned int *) tmp = 0;
		i++;
	}
	ground(img, col);
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
