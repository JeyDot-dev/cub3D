/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:37:32 by jordan            #+#    #+#             */
/*   Updated: 2024/01/30 19:19:33 by lebojo           ###   ########.fr       */
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
	else if (key == 101 || key == 14)
		return (4);
	else if (key == 113 || key == 12)
		return (5);
	return (6);
}

void	vel_normalizer(t_level *lvl)
{
	if (lvl->player.vel.x > lvl->player.max_speed)
		lvl->player.vel.x = lvl->player.max_speed;
	else if (lvl->player.vel.x < -lvl->player.max_speed)
		lvl->player.vel.x = -lvl->player.max_speed;
	if (lvl->player.vel.y > lvl->player.max_speed)
		lvl->player.vel.y = lvl->player.max_speed;
	else if (lvl->player.vel.y < -lvl->player.max_speed)
		lvl->player.vel.y = -lvl->player.max_speed;
	if (lvl->player.vel.x > 0)
		lvl->player.vel.x -= lvl->player.speed / 2;
	else if (lvl->player.vel.x < 0)
		lvl->player.vel.x += lvl->player.speed / 2;
	if (lvl->player.vel.y > 0)
		lvl->player.vel.y -= lvl->player.speed / 2;
	else if (lvl->player.vel.y < 0)
		lvl->player.vel.y += lvl->player.speed / 2;
	if (lvl->player.vel.x < 0.1 && lvl->player.vel.x > -0.1)
		lvl->player.vel.x = 0;
	if (lvl->player.vel.y < 0.1 && lvl->player.vel.y > -0.1)
		lvl->player.vel.y = 0;
}

int	rotate_cam(t_level *lvl)
{
	int	rot_speed;

	rot_speed = lvl->player.rot_speed;
	if (lvl->player.input[2])
	{
		lvl->player.dir = rotate_vector(lvl->player.dir, rot_speed);
		lvl->ray.cam_plane = rotate_vector(lvl->ray.cam_plane, rot_speed);
		return (1);
	}
	if (lvl->player.input[0])
	{
		lvl->player.dir = rotate_vector(lvl->player.dir, -rot_speed);
		lvl->ray.cam_plane = rotate_vector(lvl->ray.cam_plane, -rot_speed);
		return (1);
	}
	return (0);
}

int	player_process(t_level *lvl)
{
	int	rot;

	friction(lvl);
	rot = rotate_cam(lvl);
	if (collision(lvl, (t_vector){lvl->player.pos.x + lvl->player.vel.x,
			lvl->player.pos.y}))
		lvl->player.vel.x = 0;
	if (collision(lvl, (t_vector){lvl->player.pos.x,
			lvl->player.pos.y + lvl->player.vel.y}))
		lvl->player.vel.y = 0;
	if (vector_equal(lvl->player.vel, (t_vector){0, 0}) && !rot && !lvl->mouse)
		return (0);
	lvl->player.pos.x += lvl->player.vel.x;
	lvl->player.pos.y += lvl->player.vel.y;
	ray_caster(*lvl, &lvl->mlx);
	mlx_put_image_to_window(lvl->mlx.mlx, lvl->mlx.win, lvl->mlx.img, 0, 0);
	minimap_process(lvl);
	return (0);
}
