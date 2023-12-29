/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_mini_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:25:20 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/29 17:04:16 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
void	tmm_horizontal_coordinates(t_level lvl)
{
	int	j;

	j = 0;
	while(lvl.data.map_size.x > j)
		printf(BLU"%i"RESET, j++);
	printf("\n");
}
void	tmm_extended(int *i, int *j, t_level lvl)
{
	if (*i == (int)lvl.player.pos.y && *j == (int)lvl.player.pos.x)
	{
		printf(GRN"P"RESET);
		(*j)++;
	}
}
void	terminal_mini_map(char **map, t_level lvl)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			tmm_extended(&i, &j, lvl);
			if (map[i][j] == '1')
				printf(RED"%c"RESET, map[i][j]);
			else if (map[i][j] == '0')
				printf(WHT"%c"RESET, map[i][j]);
			else
				printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
