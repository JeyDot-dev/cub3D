/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:55:17 by jordan            #+#    #+#             */
/*   Updated: 2023/12/28 02:23:37 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_mlx(t_imgdata *img)
{
	info("Initializing mlx");
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, 1240, 720, NAME);
	img->img = mlx_new_image(img->mlx, 1240, 720);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->endian);
}

void	init(t_level *level)
{
	level->data.file_size = vector2D(-1, 0);
	level->data.map_size = vector2D(0, 0);
	level->player.pos = vector2D(0, 0);
	level->map = NULL;
	level->name = NULL;
	level->data.texture = malloc(sizeof(t_texture));
	level->data.texture[0].name = NULL;
	level->data.colors = malloc(sizeof(t_texture));
	level->data.colors[0].name = NULL;
}
