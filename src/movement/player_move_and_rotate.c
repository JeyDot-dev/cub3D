/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_and_rotate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:08:20 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/30 18:36:15 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_infos(t_level *level)
{
	terminal_mini_map(level->map, *level);
	printf("player moved to: %f, %f\n",
		level->player.pos.x, level->player.pos.y);
	printf("player dir:%f, %f\n",
		level->player.dir.x, level->player.dir.y);
}

void	rotate_player(t_level *lvl, int rot_speed)
{
	lvl->player.dir = rotate_vector(lvl->player.dir, rot_speed);
	lvl->ray.cam_plane = rotate_vector(lvl->ray.cam_plane, rot_speed);
}

void	player_move_and_rotate(t_level *level, int key)
{
	int		rot_speed;

	rot_speed = 10;
	printf("player pos: %f, %f\n", level->player.pos.x, level->player.pos.y);
	if (key == 2)
		move_forward(level);
	else if (key == 4)
		move_backward(level);
	else if (key == 1 || key == 3)
	{
		if (key == 1)
			rot_speed = -rot_speed;
		rotate_player(level, rot_speed);
	}
	print_infos(level);
	ray_caster(*level, &level->mlx);
	mlx_put_image_to_window(level->mlx.mlx,
		level->mlx.win, level->mlx.img, 0, 0);
}
