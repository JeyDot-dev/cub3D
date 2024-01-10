/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:42:55 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/10 17:35:08 by jsousa-a         ###   ########.fr       */
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

int	get_pixel_color(t_imgdata img, int x, int y)
{
	int	color;

	color = *(int *)(img.addr + (y * img.len + x * (img.bpp / 8)));
	return (color);
}

int calculate_light(int color, double dist)
{
	int	rgb[3];
	if (dist == 1)
		return (color);
	if (dist < 0.7)
		dist = 0.7;
	rgb[0] = r_value(color) / dist;
	rgb[1] = g_value(color) / dist;
	rgb[2] = b_value(color) / dist;
	return (rgbo_color(rgb[0], rgb[1], rgb[2], 0));
}

void	draw_texture_line(int y[3], t_ray r, t_texture t, t_level lvl)
{
	double	tex_step;
	double	tex_posy;
	int		i;
	int		color;

	tex_step = 1.0 * t.height / y[2];
	tex_posy = (y[0] - lvl.player.vert_dir - GAME_HEIGHT / 2 + y[2] / 2) * tex_step; //TODO: 0 = camera y
	i = y[0];
	while (i < y[1])
	{
		t.pos_y = (int)tex_posy & (t.height - 1);
		color = get_pixel_color(t.img, t.start_x, t.pos_y);
		color = calculate_light(color, r.perp_wall_dist);
		if (r.side == 1)
			color = rgbo_color(r_value(color) * 0.6, g_value(color) * 0.6, b_value(color) * 0.6, 0);
//		color = color - r.ray_dist.x + r.ray_dist.y;
//		tex_posy += tex_step;
		draw_pixel(&lvl.mlx, r.ray_count, i, color);
		tex_posy += tex_step;
		i++;
	}
}

void	draw_ray(t_imgdata *img, t_ray r, t_level lvl)
{
	int			y[3];
	int			color;
	t_texture	t;

	y[2] = (int) (GAME_HEIGHT / r.perp_wall_dist) * 0.8;
	y[0] = -y[2] / 2 + GAME_HEIGHT / 2 + lvl.player.vert_dir; //TODO: 0 = camera y
	if (y[0] < 0)
		y[0] = 0;
	y[1] = y[2] / 2 + GAME_HEIGHT / 2 + lvl.player.vert_dir; //TODO: 0 = camera y
	if (y[1] >= GAME_HEIGHT)
		y[1] = GAME_HEIGHT - 1;
	//TODO: Change 4 to max_texture
	t = set_up_texture(lvl, r, lvl.player.pos); 
	if (t.start_x >= 0 && lvl.map[r.map[1]][r.map[0]] == '1')
	{
		draw_texture_line(y, r, t, lvl);
		return ;
	}
	else
		color = 0x0000FF;
	if (r.side == 1)
		color = color * 0.6;
	draw_vertical_line(img, r.ray_count, y, color);
}
