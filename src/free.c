/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:40:02 by jordan            #+#    #+#             */
/*   Updated: 2024/02/05 17:14:50 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_texture(t_level *l)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (l->data.texture[i].name)
			free(l->data.texture[i].name);
		if (l->data.texture[i].path)
			free(l->data.texture[i].path);
		i++;
	}
}

void	free_minimap(t_level *l)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (l->minmap.player[i])
			mlx_destroy_image(l->mlx.mlx, l->minmap.player[i++]);
	}
	if (l->minmap.empty)
		mlx_destroy_image(l->mlx.mlx, l->minmap.empty);
	if (l->minmap.wall)
		mlx_destroy_image(l->mlx.mlx, l->minmap.wall);
	if (l->minmap.floor)
		mlx_destroy_image(l->mlx.mlx, l->minmap.floor);
	if (l->minmap.blck)
		mlx_destroy_image(l->mlx.mlx, l->minmap.blck);
}

void	clean_exit(t_level *l, char *msg, int err)
{
	if (err)
		error(msg);
	else
		info(msg);
	free_tab(l->map);
	free_texture(l);
	free_minimap(l);
	mlx_destroy_image(l->mlx.mlx, l->mlx.img);
	mlx_destroy_window(l->mlx.mlx, l->mlx.win);
	exit(err);
}
