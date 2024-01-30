/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:26:49 by lebojo            #+#    #+#             */
/*   Updated: 2024/01/30 18:28:21 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_level *lvl)
{
	if (lvl->player.vel.x < lvl->player.max_speed
		&& lvl->player.vel.x > -lvl->player.max_speed)
		lvl->player.vel.x += lvl->player.dir.x * lvl->player.speed;
	if (lvl->player.vel.y < lvl->player.max_speed
		&& lvl->player.vel.y > -lvl->player.max_speed)
		lvl->player.vel.y += lvl->player.dir.y * lvl->player.speed;
}

void	move_backward(t_level *lvl)
{
	if (lvl->player.vel.x < lvl->player.max_speed
		&& lvl->player.vel.x > -lvl->player.max_speed)
		lvl->player.vel.x -= lvl->player.dir.x * lvl->player.speed;
	if (lvl->player.vel.y < lvl->player.max_speed
		&& lvl->player.vel.y > -lvl->player.max_speed)
		lvl->player.vel.y -= lvl->player.dir.y * lvl->player.speed;
}

void	move_left(t_level *lvl)
{
	if (lvl->player.vel.x < lvl->player.max_speed
		&& lvl->player.vel.x > -lvl->player.max_speed)
		lvl->player.vel.x -= lvl->player.dir.y * lvl->player.speed;
	if (lvl->player.vel.y < lvl->player.max_speed
		&& lvl->player.vel.y > -lvl->player.max_speed)
		lvl->player.vel.y += lvl->player.dir.x * lvl->player.speed;
}

void	move_right(t_level *lvl)
{
	if (lvl->player.vel.x < lvl->player.max_speed
		&& lvl->player.vel.x > -lvl->player.max_speed)
		lvl->player.vel.x += lvl->player.dir.y * lvl->player.speed;
	if (lvl->player.vel.y < lvl->player.max_speed
		&& lvl->player.vel.y > -lvl->player.max_speed)
		lvl->player.vel.y -= lvl->player.dir.x * lvl->player.speed;
}
