/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_single_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:58:00 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/27 14:16:08 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

int	r_value(int color)
{
	int	red;

	red = (color >> 24 << 24 ^ color) >> 16;
	return (red);
}

int	g_value(int color)
{
	int	green;

	green = (color >> 16 << 16 ^ color) >> 8;
	return (green);
}

int	b_value(int color)
{
	int	blue;

	blue = (color >> 8 << 8 ^ color);
	return (blue);
}

int	o_value(int color)
{
	int	opacity;

	opacity = color >> 24;
	return (opacity);
}
