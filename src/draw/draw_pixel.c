/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:05:31 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/27 14:23:54 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void	draw_pixel(t_imgdata *img, int x, int y, int color)
{
	char	*colordst;

	colordst = img->addr + (img->len * y + (img->bpp / 8) * x);
	*(unsigned int *) colordst = color;
}
