/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:03:01 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/30 13:05:40 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player(t_level *lvl, t_vector dir, t_vector pos)
{
	int	i;

	if ((dir.x >= -0.3 && dir.x <= 0.3) && dir.y < 0) // NORTH
		i = 0;
	else if ((dir.x >= -0.3 && dir.x <= 0.3) && dir.y > 0) // SOUTH
		i = 4;
	else if (dir.x < 0 && (dir.y >= -0.3 && dir.y <= 0.3)) // WEST
		i = 6;
	else if (dir.x > 0 && (dir.y >= -0.3 && dir.y <= 0.3)) // EAST
		i = 2;
	else if (dir.x < 0 && dir.y < 0) // NORTH WEST
		i = 7;
	else if (dir.x > 0 && dir.y < 0) // NORTH EAST
		i = 1;
	else if (dir.x < 0 && dir.y > 0) // SOUTH WEST
		i = 5;
	else if (dir.x > 0 && dir.y > 0) // SOUTH EAST
		i = 3;
	else
		i = 0;
	draw_image(lvl, lvl->minmap.player[i], pos);
	return ;
}

void	draw_minimap(t_level *lvl)
{
	int		x;
	int		y;
	int		xmax;
	int		ymax;
	t_vector	cursor;

	y = (int)lvl->player.pos.y - 2;
	x = (int)lvl->player.pos.x - 2;
	ymax = (int)lvl->player.pos.y + 2;
	xmax = (int)lvl->player.pos.x + 2;
	set_vector2D(&cursor, 0, GAME_HEIGHT);
	while (y <= ymax)
	{
		while (x <= xmax)
		{
			if ((x >= 0 && y >= 0 && x < (int)lvl->data.map_size.x && y < (int)lvl->data.map_size.y))
			{
				if ((int)lvl->player.pos.x == x && (int)lvl->player.pos.y == y)
					draw_player(lvl, lvl->player.dir, cursor);
				else if (lvl->map[y][x] != '0')
					draw_image(lvl, lvl->minmap.wall, cursor);
				else
					draw_image(lvl, lvl->minmap.floor, cursor);
			}
			x++;
			cursor.x += 20;
		}
		x = (int)lvl->player.pos.x - 2;
		y++;
		cursor.x = 0;
		cursor.y += 20;
	}
}

void	write_coords(t_level *lvl)
{
	char	*tmp;

	tmp = ft_itoa(lvl->player.pos.x);
	tmp = add_str(tmp, ", ", 1);
	tmp = add_str(tmp, ft_itoa(lvl->player.pos.y), 3);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 10, GAME_HEIGHT, 0x00FFFFFF, tmp);
	free(tmp);
}

void	draw_txt_minimap(t_level *lvl)
{
	char	*tmp;

	tmp = malloc(100);
	sprintf(tmp, "%c %c %c %c %c\n", lvl->map[(int)lvl->player.pos.y - 2][(int)lvl->player.pos.x - 2], lvl->map[(int)lvl->player.pos.y - 2][(int)lvl->player.pos.x - 1], lvl->map[(int)lvl->player.pos.y - 2][(int)lvl->player.pos.x], lvl->map[(int)lvl->player.pos.y - 2][(int)lvl->player.pos.x + 1], lvl->map[(int)lvl->player.pos.y - 2][(int)lvl->player.pos.x + 2]);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 10, 620, 0x00FFFFFF, tmp);
	free(tmp);
	tmp = malloc(100);
	sprintf(tmp, "%c %c %c %c %c\n", lvl->map[(int)lvl->player.pos.y - 1][(int)lvl->player.pos.x - 2], lvl->map[(int)lvl->player.pos.y - 1][(int)lvl->player.pos.x - 1], lvl->map[(int)lvl->player.pos.y - 1][(int)lvl->player.pos.x], lvl->map[(int)lvl->player.pos.y - 1][(int)lvl->player.pos.x + 1], lvl->map[(int)lvl->player.pos.y - 1][(int)lvl->player.pos.x + 2]);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 10, 640, 0x00FFFFFF, tmp);
	free(tmp);
	tmp = malloc(100);
	sprintf(tmp, "%c %c %c %c %c\n", lvl->map[(int)lvl->player.pos.y][(int)lvl->player.pos.x - 2], lvl->map[(int)lvl->player.pos.y][(int)lvl->player.pos.x - 1], 'P', lvl->map[(int)lvl->player.pos.y][(int)lvl->player.pos.x + 1], lvl->map[(int)lvl->player.pos.y][(int)lvl->player.pos.x + 2]);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 10, 660, 0x00FFFFFF, tmp);
	free(tmp);
	tmp = malloc(100);
	sprintf(tmp, "%c %c %c %c %c\n", lvl->map[(int)lvl->player.pos.y + 1][(int)lvl->player.pos.x - 2], lvl->map[(int)lvl->player.pos.y + 1][(int)lvl->player.pos.x - 1], lvl->map[(int)lvl->player.pos.y + 1][(int)lvl->player.pos.x], lvl->map[(int)lvl->player.pos.y + 1][(int)lvl->player.pos.x + 1], lvl->map[(int)lvl->player.pos.y + 1][(int)lvl->player.pos.x + 2]);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 10, 680, 0x00FFFFFF, tmp);
	free(tmp);
	tmp = malloc(100);
	sprintf(tmp, "%c %c %c %c %c\n", lvl->map[(int)lvl->player.pos.y + 2][(int)lvl->player.pos.x - 2], lvl->map[(int)lvl->player.pos.y + 2][(int)lvl->player.pos.x - 1], lvl->map[(int)lvl->player.pos.y + 2][(int)lvl->player.pos.x], lvl->map[(int)lvl->player.pos.y + 2][(int)lvl->player.pos.x + 1], lvl->map[(int)lvl->player.pos.y + 2][(int)lvl->player.pos.x + 2]);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 10, 700, 0x00FFFFFF, tmp);
	free(tmp);
}

int	minimap_process(t_level *lvl)
{
	write_coords(lvl);
	draw_image(lvl, lvl->minmap.blck, vector2D(0, GAME_HEIGHT));
	draw_minimap(lvl);
	return (0);
}
