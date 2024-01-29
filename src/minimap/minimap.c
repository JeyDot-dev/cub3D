/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:03:01 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/29 22:21:10 by lebojo           ###   ########.fr       */
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
	char	*tmp;

	draw_image(lvl, lvl->data.blck, vector2D(0, GAME_HEIGHT));
	tmp = ft_itoa((int)lvl->player.pos.x);
	tmp = add_str(tmp, ", ", 1);
	tmp = add_str(tmp, ft_itoa((int)lvl->player.pos.y), 3);
	free(tmp);
	
	tmp = malloc(100);
	sprintf(tmp, "%c%c%c%c%c\n", lvl->map[(int)lvl->player.pos.y - 2][(int)lvl->player.pos.x - 2], lvl->map[(int)lvl->player.pos.y - 2][(int)lvl->player.pos.x - 1], lvl->map[(int)lvl->player.pos.y - 2][(int)lvl->player.pos.x], lvl->map[(int)lvl->player.pos.y - 2][(int)lvl->player.pos.x + 1], lvl->map[(int)lvl->player.pos.y - 2][(int)lvl->player.pos.x + 2]);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 10, 620, 0x00FFFFFF, tmp);
	free(tmp);
	tmp = malloc(100);
	sprintf(tmp, "%c%c%c%c%c\n", lvl->map[(int)lvl->player.pos.y - 1][(int)lvl->player.pos.x - 2], lvl->map[(int)lvl->player.pos.y - 1][(int)lvl->player.pos.x - 1], lvl->map[(int)lvl->player.pos.y - 1][(int)lvl->player.pos.x], lvl->map[(int)lvl->player.pos.y - 1][(int)lvl->player.pos.x + 1], lvl->map[(int)lvl->player.pos.y - 1][(int)lvl->player.pos.x + 2]);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 10, 640, 0x00FFFFFF, tmp);
	free(tmp);
	tmp = malloc(100);
	sprintf(tmp, "%c%c%c%c%c\n", lvl->map[(int)lvl->player.pos.y][(int)lvl->player.pos.x - 2], lvl->map[(int)lvl->player.pos.y][(int)lvl->player.pos.x - 1], 'P', lvl->map[(int)lvl->player.pos.y][(int)lvl->player.pos.x + 1], lvl->map[(int)lvl->player.pos.y][(int)lvl->player.pos.x + 2]);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 10, 660, 0x00FFFFFF, tmp);
	free(tmp);
	tmp = malloc(100);
	sprintf(tmp, "%c%c%c%c%c\n", lvl->map[(int)lvl->player.pos.y + 1][(int)lvl->player.pos.x - 2], lvl->map[(int)lvl->player.pos.y + 1][(int)lvl->player.pos.x - 1], lvl->map[(int)lvl->player.pos.y + 1][(int)lvl->player.pos.x], lvl->map[(int)lvl->player.pos.y + 1][(int)lvl->player.pos.x + 1], lvl->map[(int)lvl->player.pos.y + 1][(int)lvl->player.pos.x + 2]);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 10, 680, 0x00FFFFFF, tmp);
	free(tmp);
	tmp = malloc(100);
	sprintf(tmp, "%c%c%c%c%c\n", lvl->map[(int)lvl->player.pos.y + 2][(int)lvl->player.pos.x - 2], lvl->map[(int)lvl->player.pos.y + 2][(int)lvl->player.pos.x - 1], lvl->map[(int)lvl->player.pos.y + 2][(int)lvl->player.pos.x], lvl->map[(int)lvl->player.pos.y + 2][(int)lvl->player.pos.x + 1], lvl->map[(int)lvl->player.pos.y + 2][(int)lvl->player.pos.x + 2]);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 10, 700, 0x00FFFFFF, tmp);
	free(tmp);
	
	return (0);
}
