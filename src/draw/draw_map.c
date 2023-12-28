/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:03:01 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/27 18:03:11 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void	draw_map(t_level level, t_imgdata img)
{
	t_vector	origin;
	t_vector	tmp_fix;

	info("Drawing map...");
	origin.x = 0;
	origin.y = 0;
	tmp_fix.x = 0;
	tmp_fix.y = 0;
	while (origin.y < level.data.map_size.y)
	{
		while (level.map[origin.y][origin.x] != '\0')
		{
			ft_fprintf(2, "%c", level.map[origin.y][origin.x]);
			if (level.map[origin.y][origin.x] == '1')
				draw_square(tmp_fix, img, '1');
			else if (level.map[origin.y][origin.x] == '0')
				draw_square(tmp_fix, img, '0');
			if (level.map[origin.y][origin.x] == '\t')
				tmp_fix.x += 3;
			origin.x++;
			tmp_fix.x++;
		}
		ft_putchar_fd('\n', 2);
		origin.x = 0;
		tmp_fix.x = 0;
		tmp_fix.y++;
		origin.y++;
	}
}
