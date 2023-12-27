/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_gradient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:22:18 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/27 14:22:21 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

int	inc_color(int color, int target_color, int pixels)
{
	int	new_color;

	if (pixels <= 0)
		pixels = 1;
	new_color = color;
	if (color < target_color)
	{
		new_color = color + ((target_color - color) / pixels);
		if (new_color == color)
			new_color++;
		if (new_color > target_color)
			new_color = target_color;
	}
	else if (color > target_color)
	{
		new_color = color - ((color - target_color) / pixels);
		if (new_color == color)
			new_color--;
		if (new_color < target_color)
			new_color = target_color;
	}
	return (new_color);
}

int	smooth_colors(int color, int target_color, int pixels)
{
	int	r;
	int	g;
	int	b;
	int	o;

	r = inc_color(r_value(color), r_value(target_color), pixels);
	g = inc_color(g_value(color), g_value(target_color), pixels);
	b = inc_color(b_value(color), b_value(target_color), pixels);
	o = inc_color(o_value(color), o_value(target_color), pixels);
	return (rgbo_color(r, g, b, o));
}
