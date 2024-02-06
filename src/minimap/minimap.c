/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:03:01 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/02/06 05:34:39 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player(t_level *lvl, t_vector dir, t_vector pos)
{
	int	i;

	if ((dir.x >= -0.3 && dir.x <= 0.3) && dir.y < 0)
		i = 0;
	else if ((dir.x >= -0.3 && dir.x <= 0.3) && dir.y > 0)
		i = 4;
	else if (dir.x < 0 && (dir.y >= -0.3 && dir.y <= 0.3))
		i = 6;
	else if (dir.x > 0 && (dir.y >= -0.3 && dir.y <= 0.3))
		i = 2;
	else if (dir.x < 0 && dir.y < 0)
		i = 7;
	else if (dir.x > 0 && dir.y < 0)
		i = 1;
	else if (dir.x < 0 && dir.y > 0)
		i = 5;
	else if (dir.x > 0 && dir.y > 0)
		i = 3;
	else
		i = 0;
	draw_image(lvl, lvl->minmap.player[i], pos);
	return ;
}

void	draw_minimap_process(t_level *lvl, int x, int y, t_vector cursor)
{
	if ((x >= 0 && y >= 0 && x < (int)lvl->data.map_size.x
			&& y < (int)lvl->data.map_size.y))
	{
		if ((int)lvl->player.pos.x == x && (int)lvl->player.pos.y == y)
			draw_player(lvl, lvl->player.dir, cursor);
		else if (!ft_strchr("0NSEW", lvl->map[y][x]))
			draw_image(lvl, lvl->minmap.wall, cursor);
		else
			draw_image(lvl, lvl->minmap.floor, cursor);
	}
}

void	draw_minimap(t_level *lvl)
{
	int			x;
	int			y;
	int			xmax;
	int			ymax;
	t_vector	cursor;

	y = (int)lvl->player.pos.y - 2;
	x = (int)lvl->player.pos.x - 2;
	ymax = (int)lvl->player.pos.y + 2;
	xmax = (int)lvl->player.pos.x + 2;
	set_vector2d(&cursor, 0, GAME_HEIGHT);
	while (y <= ymax)
	{
		while (x <= xmax)
		{
			draw_minimap_process(lvl, x, y, cursor);
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
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 120,
		GAME_HEIGHT + 60, 0x00FFFFFF, tmp);
	tmp = add_str("Map: ", lvl->name, 0);
	mlx_string_put(lvl->mlx.mlx, lvl->mlx.win, 120,
		GAME_HEIGHT + 40, 0x00FFFFFF, tmp);
	free(tmp);
}

int	minimap_process(t_level *lvl)
{
	draw_image(lvl, lvl->minmap.blck, vector2d(0, GAME_HEIGHT));
	write_coords(lvl);
	draw_minimap(lvl);
	return (0);
}
