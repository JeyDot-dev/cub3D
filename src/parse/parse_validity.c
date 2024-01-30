/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 03:30:06 by jchapell          #+#    #+#             */
/*   Updated: 2024/01/30 21:16:58 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	border_check(char **map)
{
	t_vector	i;

	set_vector2d(&i, 1, 1);
	while (map[(int)i.y])
	{
		i.x = 1;
		while (map[(int)i.y][(int)i.x])
		{
			if (map[(int)i.y][(int)i.x] == '0')
				if (i.y == 0 || i.x == 0 || !map[(int)i.y + 1]
					|| !map[(int)i.y][(int)i.x + 1]
					|| (map[(int)i.y][(int)i.x - 1] == ' '
					|| map[(int)i.y][(int)i.x + 1] == ' '
					|| map[(int)i.y - 1][(int)i.x] == ' '
					|| map[(int)i.y + 1][(int)i.x] == ' '))
					return (1);
			i.x++;
		}
		i.y++;
	}
	return (0);
}

int	parse_validity(t_level *lvl)
{
	if (border_check(lvl->map))
		return (error("Map is not closed!"));
	info("Map ok!");
	return (0);
}
