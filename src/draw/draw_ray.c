/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:42:55 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/04 18:47:39 by jsousa-a         ###   ########.fr       */
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
int		get_pixel_color(t_imgdata img, int x, int y)
{
	int	color;

	color = *(int *)(img.addr + (y * img.len + x * (img.bpp / 8)));
	return (color);
}
void	draw_texture_line(int y[2], int x, t_texture t, t_imgdata *img)
{
	double	tex_step;
	double	tex_posy;
	int		i;

	tex_step = 1.0 * t.height / (y[1] - y[0]);
	tex_posy = (y[0] - GAME_HEIGHT / 2 + (y[1] - y[0]) / 2) * tex_step;
	i = y[0];
	while (i < y[1])
	{
		t.pos_y = (int)tex_posy & (t.height - 1);
		tex_posy += tex_step;
		draw_pixel(img, x, i, get_pixel_color(t.img, t.start_x, t.pos_y));
		tex_posy += tex_step;
		i++;
	}
}

void	draw_ray(t_imgdata *img, t_ray r, t_level lvl)
{
	int			y[2];
	int			color;
	t_texture	t;

	y[0] = (int) -(GAME_HEIGHT / r.perp_wall_dist) / 2 + GAME_HEIGHT / 2;
	if (y[0] < 0)
		y[0] = 0;
	y[1] = (int) (GAME_HEIGHT / r.perp_wall_dist) / 2 + GAME_HEIGHT / 2;
	if (y[1] >= GAME_HEIGHT)
		y[1] = GAME_HEIGHT - 1;
	t = set_up_texture(lvl.data.texture, r, lvl.player.pos); 
	if (t.start_x >= 0 && lvl.map[r.map[1]][r.map[0]] == '1')
	{
		draw_texture_line(y, r.ray_count, t, img);
		return ;
	}
	else
		color = 0x0000FF;
	if (r.side == 1)
		color = color / 2;
	draw_vertical_line(img, r.ray_count, y, color);
}
