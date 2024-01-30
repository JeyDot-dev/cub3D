/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:26:01 by lebojo            #+#    #+#             */
/*   Updated: 2024/01/30 18:26:40 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	collision(t_level *lvl, t_vector pos)
{
	if (!ft_strchr("0NSEW", lvl->map[(int)pos.y][(int)pos.x]))
		return (1);
	return (0);
}

void	friction(t_level *lvl)
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
