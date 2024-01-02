/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:55:17 by jordan            #+#    #+#             */
/*   Updated: 2024/01/02 17:03:43 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_mlx(t_imgdata *img)
{
	info("Initializing mlx");
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, WIN_WIDTH, WIN_HEIGHT, NAME);
	img->img = mlx_new_image(img->mlx, WIN_WIDTH, WIN_HEIGHT);
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
}

void	init(t_level *level)
{
	level->data.file_size = vector2D(-1, 0);
	level->data.map_size = vector2D(0, 0);
	level->player.pos = vector2D(0, 0);
	level->player.max_speed = 1;
	level->player.speed = 0.1;
	level->player.vel = vector2D(0, 0);
	level->player.rot_speed = 1;
	level->player.dir = vector2D(0, 0);
	level->player.fov = 90;
	input_init(level);
	level->map = NULL;
	level->name = NULL;
	level->data.texture = malloc(sizeof(t_texture));
	level->data.texture[0].name = NULL;
	level->data.colors = malloc(sizeof(t_texture));
	level->data.colors[0].name = NULL;
}
