/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:47:09 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/10 13:32:32 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int pick_cardinal_texture(t_ray r, int max_texture)
{
	int	pick;
	if (r.side == 0 && r.ray_dir.x > 0)
		pick = 0;
	else if (r.side == 0 && r.ray_dir.x < 0)
		pick = 1;
	else if (r.side == 1 && r.ray_dir.y > 0)
		pick = 2;
	else if (r.side == 1 && r.ray_dir.y < 0)
		pick = 3;
	else
		return (-1);
	pick = pick + (r.hit - 1) * 4;
	if (pick < max_texture)
		return (pick);
	return (-1);

}

t_texture	set_up_texture(t_level lvl, t_ray r, t_vector pos)
{
	t_texture	t;
	int			pick;
	double		wall_x;

//	TODO: Change 4 to max_texture
	pick = pick_cardinal_texture(r, 4);
	if (pick == -1 || lvl.data.texture[pick].img.img == NULL)
	{
		t.start_x = -1;
		return (t);
	}
	t = lvl.data.texture[pick];
	if (r.side == 0)
		wall_x = pos.y + r.perp_wall_dist * r.ray_dir.y;
	else
		wall_x = pos.x + r.perp_wall_dist * r.ray_dir.x;
	wall_x -= floor(wall_x);
	t.start_x = (int)(wall_x * (double)t.width);
	if (r.side == 0 && r.ray_dir.x > 0)
		t.start_x = t.width - t.start_x - 1;
	else if (r.side == 1 && r.ray_dir.y < 0)
		t.start_x = t.width - t.start_x - 1;
	return (t);
}
