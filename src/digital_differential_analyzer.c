/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digital_differential_analyzer.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:56:05 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/30 17:39:26 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_ray	dda(t_ray r, char **map)
{
	while (r.hit == 0)
	{
		if (r.ray_dist.x < r.ray_dist.y)
		{
			r.ray_dist.x += r.delta_dist.x;
			r.map[0] += (int) r.step.x;
			r.side = 0;
		}
		else
		{
			r.ray_dist.y += r.delta_dist.y;
			r.map[1] += (int) r.step.y;
			r.side = 1;
		}
		if (map[r.map[1]][r.map[0]] > '0' && map[r.map[1]][r.map[0]] <= '9')
			r.hit = map[r.map[1]][r.map[0]] - '0';
	}
	return (r);
}
