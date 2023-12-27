/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:55:17 by jordan            #+#    #+#             */
/*   Updated: 2023/12/27 16:08:18 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init(t_level *level)
{
	level->data.file_size = vector2D(-1, 0);
	level->data.map_size = vector2D(37, 14);
	level->player.pos = vector2D(0, 0);
	level->map = NULL;
	level->name = NULL;
	level->data.texture = malloc(sizeof(t_texture));
	level->data.texture[0].name = NULL;
	level->data.colors = malloc(sizeof(t_texture));
	level->data.colors[0].name = NULL;
}
