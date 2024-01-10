/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:03:01 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/10 17:21:11 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap(t_level *level)
{
	t_vector	origin;
	t_vector	tmp_fix;

	origin.x = 0;
	origin.y = 0;
	tmp_fix.x = 0;
	tmp_fix.y = 0;
	while (origin.y < level->data.map_size.y)
	{
		while (level->map[(int)origin.y][(int)origin.x] != '\0')
		{
			if (level->map[(int)origin.y][(int)origin.x] == '1')
				draw_square(tmp_fix, level->mlx, '1');
			else if (level->map[(int)origin.y][(int)origin.x] == '0')
				draw_square(tmp_fix, level->mlx, '0');
			if (level->map[(int)origin.y][(int)origin.x] == '\t')
				tmp_fix.x += 3;
			origin.x++;
			tmp_fix.x++;
		}
		origin.x = 0;
		tmp_fix.x = 0;
		tmp_fix.y++;
		origin.y++;
	}
}

void	draw_player(t_level *lvl)
{
	(void)lvl;
	return ;
}

int	minimap_process(t_level *lvl)
{
	info("Drawing minimap...");
	terminal_mini_map(lvl->map, *lvl);
	return (0);
}
