/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:37:32 by jordan            #+#    #+#             */
/*   Updated: 2024/01/02 17:07:18 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	int_to_dir(int key)
{
	if (key == 2 || key == 124
		|| key == 65363 || key == 100)
		return (2);
	else if (key == 0 || key == 123
		|| key == 65361 || key == 97)
		return (0);
	else if (key == 13 || key == 126
		|| key == 65362 || key == 119)
		return (1);
	else if (key == 1 || key == 125
		|| key == 65364 || key == 115)
		return (3);
	return (0);
}

void friction(t_level *lvl)
{
	if (lvl->player.vel.x > 0)
		lvl->player.vel.x -= lvl->player.speed * 2;
	else if (lvl->player.vel.x < 0)
		lvl->player.vel.x += lvl->player.speed * 2;
	else
		lvl->player.vel.x = 0;
	if (lvl->player.vel.y > 0)
		lvl->player.vel.y -= lvl->player.speed * 2;
	else if (lvl->player.vel.y < 0)
		lvl->player.vel.y += lvl->player.speed * 2;
	else
		lvl->player.vel.y = 0;
	if (lvl->player.vel.x < lvl->player.max_speed && lvl->player.vel.x > -lvl->player.max_speed)
	{
		if (lvl->player.input[0] == 1)
			lvl->player.vel.x -= lvl->player.speed;
		if (lvl->player.input[2] == 1)
			lvl->player.vel.x += lvl->player.speed;
	}
	if (lvl->player.vel.y < lvl->player.max_speed && lvl->player.vel.y > -lvl->player.max_speed)
	{
		if (lvl->player.input[1] == 1)
			lvl->player.vel.y -= lvl->player.speed;
		if (lvl->player.input[3] == 1)
			lvl->player.vel.y += lvl->player.speed;
	}
}

void rotate_cam(t_level *lvl)
{
	if (lvl->player.input[4])
		printf("rotate cam left\n");
	if (lvl->player.input[5])
		printf("rotate cam right\n");
}

int player_move(t_level *lvl)
{
	friction(lvl);
	rotate_cam(lvl);
	lvl->player.pos.x += lvl->player.vel.x;
	lvl->player.pos.y += lvl->player.vel.y;
	ray_caster(*lvl, &lvl->mlx);
	mlx_put_image_to_window(lvl->mlx.mlx, lvl->mlx.win, lvl->mlx.img, 0, 0);
	return (0);
}