/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:47:09 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/03 21:49:59 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int pick_cardinal_texture(t_ray r)
{
	if (r.side == 0 && r.ray_dir.x > 0)
		return (0);
	else if (r.side == 0 && r.ray_dir.x < 0)
		return (1);
	else if (r.side == 1 && r.ray_dir.y > 0)
		return (2);
	else if (r.side == 1 && r.ray_dir.y < 0)
		return (3);
	return (-1);
}

t_texture	set_up_texture(t_texture *texture, t_ray r, t_vector pos)
{
	t_texture	t;
	int			pick;
	double		wall_x;

	pick = pick_cardinal_texture(r);
	if (pick == -1)
	{
		t.start_x = -1;
		return (t);
	}
	t = texture[pick];
	if (r.side == 0)
		wall_x = pos.y + r.perp_wall_dist * r.ray_dir.y;
	else
		wall_x = pos.x + r.perp_wall_dist * r.ray_dir.x;
	wall_x -= floor(wall_x);
	t.start_x = (int)(wall_x * (double)t.width);
	if (r.side == 0 && r.ray_dir.x > 0)
		t.start_x = t.width - t.start_x - 1;
	if (r.side == 1 && r.ray_dir.y < 0)
		t.start_x = t.width - t.start_x - 1;
	return (t);
}
