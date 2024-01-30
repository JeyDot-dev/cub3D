/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:05:40 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/30 18:47:15 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector_line	switch_line(t_vector_line line)
{
	int	buffer;

	buffer = line.start.x;
	line.start.x = line.end.x;
	line.end.x = buffer;
	buffer = line.start.y;
	line.start.y = line.end.y;
	line.end.y = buffer;
	buffer = line.color;
	line.color = line.color2;
	line.color2 = buffer;
	return (line);
}

t_vector_line	delta_and_inc_setup(t_vector_line line)
{
	line.dx = line.end.x - line.start.x;
	line.dy = line.end.y - line.start.y;
	line.inc[0] = 1;
	if (line.dx > line.dy)
		line.inc[1] = line.start.x;
	else
		line.inc[1] = line.start.y;
	if (line.dx > line.dy && line.dy < 0)
	{
		line.inc[0] = -1;
		line.dy = -line.dy;
	}
	else if (line.dy > line.dx && line.dx < 0)
	{
		line.inc[0] = -1;
		line.dx = -line.dx;
	}
	return (line);
}

void	horizontal_line(t_imgdata *img, t_vector_line line)
{
	line = delta_and_inc_setup(line);
	line.e = (2 * line.dy) - line.dx;
	while (line.inc[1] <= line.end.x)
	{
		if (line.start.x < 1920 && line.start.y < 1080
			&& line.start.x >= 0 && line.start.y >= 0)
			draw_pixel(img, line.start.x, line.start.y, line.color);
		line.color = smooth_colors(line.color, line.color2,
				line.end.x - line.start.x);
		if (line.e > 0)
		{
			line.start.y += line.inc[0];
			line.e = line.e + (2 * (line.dy - line.dx));
		}
		else
			line.e = line.e + 2 * line.dy;
		line.start.x += 1;
		line.inc[1] += 1;
	}
}

void	vertical_line(t_imgdata *img, t_vector_line line)
{
	line = delta_and_inc_setup(line);
	line.e = (2 * line.dx) - line.dy;
	while (line.inc[1] <= line.end.y)
	{
		if (line.start.x < 1920 && line.start.y < 1080
			&& line.start.x >= 0 && line.start.y >= 0)
			draw_pixel(img, line.start.x, line.start.y, line.color);
		line.color = smooth_colors(line.color, line.color2,
				line.end.y - line.start.y);
		if (line.e > 0)
		{
			line.start.x += line.inc[0];
			line.e = line.e + (2 * (line.dx - line.dy));
		}
		else
			line.e = line.e + 2 * line.dx;
		line.start.y += 1;
		line.inc[1] += 1;
	}
}

void	draw_line(t_imgdata *img, t_vector_line line)
{
	int	dy;
	int	dx;

	dy = ft_abs(line.end.y - line.start.y);
	dx = ft_abs(line.end.x - line.start.x);
	if (dy < dx)
	{
		if (line.start.x > line.end.x)
			line = switch_line(line);
		horizontal_line(img, line);
	}
	else
	{
		if (line.start.y > line.end.y)
			line = switch_line(line);
		vertical_line(img, line);
	}
}
