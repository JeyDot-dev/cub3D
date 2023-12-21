/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:55:17 by jordan            #+#    #+#             */
/*   Updated: 2023/12/21 18:04:19 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init(t_level *level)
{
	level->data.size = vector2D(-1, 0);
	level->player.pos = vector2D(0, 0);
	level->map_raw = NULL;
	level->map = NULL;
	level->name = NULL;
}