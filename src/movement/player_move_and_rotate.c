/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_and_rotate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:08:20 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/29 16:37:55 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
void print_infos(t_level *level)
{
	terminal_mini_map(level->map, *level);
	printf("player moved to: %f, %f\n", level->player.pos.x, level->player.pos.y);
	printf("player dir:%f, %f\n", level->player.dir.x, level->player.dir.y);
}

void move_forward(t_level *lvl, double move_speed)
{
	if (lvl->map[(int)(lvl->player.pos.y + lvl->player.dir.y * move_speed)][(int)lvl->player.pos.x] == '0')
		lvl->player.pos.x += lvl->player.dir.x * move_speed;
	if (lvl->map[(int)lvl->player.pos.y][(int)(lvl->player.pos.x + lvl->player.dir.x * move_speed)] == '0')
		lvl->player.pos.y += lvl->player.dir.y * move_speed;
}

void move_backward(t_level *lvl, double move_speed)
{
	if (lvl->map[(int)(lvl->player.pos.y - lvl->player.dir.y * move_speed)][(int)lvl->player.pos.x] == '0')
		lvl->player.pos.x -= lvl->player.dir.x * move_speed;
	if (lvl->map[(int)lvl->player.pos.y][(int)(lvl->player.pos.x - lvl->player.dir.x * move_speed)] == '0')
		lvl->player.pos.y -= lvl->player.dir.y * move_speed;
}

void rotate_player(t_level *lvl, int rot_speed)
{
	lvl->player.dir = rotate_vector(lvl->player.dir, rot_speed);
	lvl->ray.cam_plane = rotate_vector(lvl->ray.cam_plane, rot_speed);
}

void player_move_and_rotate(t_level *level, int key)
{
	double	move_speed;
	int		rot_speed;

	move_speed = 0.1;
	rot_speed = 10;
	printf("player pos: %f, %f\n", level->player.pos.x, level->player.pos.y);
	if (key == 2)
		move_forward(level, move_speed);
	else if (key == 4)
		move_backward(level, move_speed);
	else if (key == 1 || key == 3)
	{
		if (key == 1)
			rot_speed = -rot_speed;
		rotate_player(level, rot_speed);
	}
	print_infos(level);
	ray_caster(*level, &level->mlx);
	mlx_put_image_to_window(level->mlx.mlx, level->mlx.win, level->mlx.img, 0, 0);
}
