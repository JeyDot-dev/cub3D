/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:37:32 by jordan            #+#    #+#             */
/*   Updated: 2024/01/10 14:37:09 by jsousa-a         ###   ########.fr       */
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
	else if (key == 101)
		return (4);
	else if (key == 113)
		return (5);
	return (0);
}

void move_forward(t_level *lvl)
{
	if (lvl->player.vel.x < lvl->player.max_speed && lvl->player.vel.x > -lvl->player.max_speed)
		lvl->player.vel.x += lvl->player.dir.x * lvl->player.speed;
	if (lvl->player.vel.y < lvl->player.max_speed && lvl->player.vel.y > -lvl->player.max_speed)
		lvl->player.vel.y += lvl->player.dir.y * lvl->player.speed;
}

void move_backward(t_level *lvl)
{
	if (lvl->player.vel.x < lvl->player.max_speed && lvl->player.vel.x > -lvl->player.max_speed)
		lvl->player.vel.x -= lvl->player.dir.x * lvl->player.speed;
	if (lvl->player.vel.y < lvl->player.max_speed && lvl->player.vel.y > -lvl->player.max_speed)
		lvl->player.vel.y -= lvl->player.dir.y * lvl->player.speed;
}

void move_left(t_level *lvl)
{
	if (lvl->player.vel.x < lvl->player.max_speed && lvl->player.vel.x > -lvl->player.max_speed)
		lvl->player.vel.x -= lvl->player.dir.y * lvl->player.speed;
	if (lvl->player.vel.y < lvl->player.max_speed && lvl->player.vel.y > -lvl->player.max_speed)
		lvl->player.vel.y += lvl->player.dir.x * lvl->player.speed;
}

void move_right(t_level *lvl)
{
	if (lvl->player.vel.x < lvl->player.max_speed && lvl->player.vel.x > -lvl->player.max_speed)
		lvl->player.vel.x += lvl->player.dir.y * lvl->player.speed;
	if (lvl->player.vel.y < lvl->player.max_speed && lvl->player.vel.y > -lvl->player.max_speed)
		lvl->player.vel.y -= lvl->player.dir.x * lvl->player.speed;
}

void vel_normalizer(t_level *lvl)
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

void friction(t_level *lvl)
{
	vel_normalizer(lvl);
	if (lvl->player.input[1] == 1)
		move_forward(lvl);
	if (lvl->player.input[3] == 1)
		move_backward(lvl);
	if (lvl->player.input[2] == 1)
		move_left(lvl);
	if (lvl->player.input[0] == 1)
		move_right(lvl);
}

void rotate_cam(t_level *lvl)
{
	int	rot_speed;

	rot_speed = lvl->player.rot_speed;
	if (lvl->player.input[4])
	{
		lvl->player.dir = rotate_vector(lvl->player.dir, rot_speed);
		lvl->ray.cam_plane = rotate_vector(lvl->ray.cam_plane, rot_speed);
	}
	if (lvl->player.input[5])
	{
		lvl->player.dir = rotate_vector(lvl->player.dir, -rot_speed);
		lvl->ray.cam_plane = rotate_vector(lvl->ray.cam_plane, -rot_speed);
	}
}

int player_process(t_level *lvl)
{
	minimap_process(lvl);
	friction(lvl);
	rotate_cam(lvl);
	lvl->player.pos.x += lvl->player.vel.x;
	lvl->player.pos.y += lvl->player.vel.y;
	ray_caster(*lvl, &lvl->mlx);
	mlx_put_image_to_window(lvl->mlx.mlx, lvl->mlx.win, lvl->mlx.img, 0, 0);
	return (0);
}
