/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:42:55 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/29 16:43:10 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_vertical_line(t_imgdata *img, int x, int y[2], int color)
{
	int	i;

	i = y[0];
	while (i < y[1])
	{
		draw_pixel(img, x, i, color);
		i++;
	}
}

void	draw_ray(t_imgdata *img, t_ray r, char **map)
{
	int	y[2];
	int	color;

	y[0] = (int) -(WIN_HEIGHT / r.perp_wall_dist) / 2 + WIN_HEIGHT / 2;
	if (y[0] < 0)
		y[0] = 0;
	y[1] = (int) (WIN_HEIGHT / r.perp_wall_dist) / 2 + WIN_HEIGHT / 2;
	if (y[1] >= WIN_HEIGHT)
		y[1] = WIN_HEIGHT - 1;
	if (map[r.map[1]][r.map[0]] == '1')
	{
		color = rgbo_color(120, 160, 70, 0);
	}
	else
		color = 0x0000FF;
	if (r.side == 1)
		color = color / 2;
	draw_vertical_line(img, r.ray_count, y, color);

}
