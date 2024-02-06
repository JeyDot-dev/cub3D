/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:55:17 by jordan            #+#    #+#             */
/*   Updated: 2024/02/06 05:27:28 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_mlx(t_imgdata *img)
{
	info("Initializing mlx");
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, WIN_WIDTH, WIN_HEIGHT, NAME);
	img->img = mlx_new_image(img->mlx, WIN_WIDTH, GAME_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->endian);
}

void	input_init(t_level *level)
{
	level->player.input[0] = 0;
	level->player.input[1] = 0;
	level->player.input[2] = 0;
	level->player.input[3] = 0;
	level->player.input[4] = 0;
	level->player.input[5] = 0;
	level->player.input[6] = 0;
	level->player.input[7] = 0;
	level->player.input[8] = 0;
}

void	init_textures(t_level *lvl)
{
	lvl->minmap.blck = path_to_image(lvl, "./textures/blck.xpm");
	lvl->minmap.wall = path_to_image(lvl, "./textures/map/wall.xpm");
	lvl->minmap.floor = path_to_image(lvl, "./textures/map/floor.xpm");
	lvl->minmap.player[0] = path_to_image(lvl, "./textures/map/p/player_0.xpm");
	lvl->minmap.player[1] = path_to_image(lvl, "./textures/map/p/player_1.xpm");
	lvl->minmap.player[2] = path_to_image(lvl, "./textures/map/p/player_2.xpm");
	lvl->minmap.player[3] = path_to_image(lvl, "./textures/map/p/player_3.xpm");
	lvl->minmap.player[4] = path_to_image(lvl, "./textures/map/p/player_4.xpm");
	lvl->minmap.player[5] = path_to_image(lvl, "./textures/map/p/player_5.xpm");
	lvl->minmap.player[6] = path_to_image(lvl, "./textures/map/p/player_6.xpm");
	lvl->minmap.player[7] = path_to_image(lvl, "./textures/map/p/player_7.xpm");
	lvl->data.texture[0].name = NULL;
	lvl->data.texture[1].name = NULL;
	lvl->data.texture[2].name = NULL;
	lvl->data.texture[3].name = NULL;
	lvl->data.texture[0].path = NULL;
	lvl->data.texture[1].path = NULL;
	lvl->data.texture[2].path = NULL;
	lvl->data.texture[3].path = NULL;
}

void	init(t_level *level)
{
	level->data.file_size = vector2d(-1, 0);
	level->data.map_size = vector2d(0, 0);
	level->player.pos = vector2d(0, 0);
	level->rev_ctrl = 1;
	level->data.max_texture = 4;
	level->player.vert_dir = 0;
	level->player.max_speed = 1;
	level->player.speed = 0.1;
	level->player.vel = vector2d(0, 0);
	level->player.rot_speed = 5;
	level->player.dir = vector2d(0, 0);
	level->ray.ray_count = 0;
	input_init(level);
	level->map = NULL;
	level->name = NULL;
	init_textures(level);
	level->data.floor = 0;
	level->data.ceiling = 0;
	mlx_mouse_move(level->mlx.win, WIN_WIDTH / 2, GAME_HEIGHT / 2);
}
