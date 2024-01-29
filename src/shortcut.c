/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 04:21:33 by lebojo            #+#    #+#             */
/*   Updated: 2024/01/29 20:51:09 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*path_to_image(t_level *l, char *path)
{
	int		x;
	int		y;

	return (mlx_xpm_file_to_image(l->mlx.mlx, path, &x, &y));
}

void	draw_image(t_level *l, char *path, t_vector p)
{
	char	*img;

	img = path_to_image(l, path);
	mlx_put_image_to_window(l->mlx.mlx, l->mlx.win, img, (int)p.x, (int)p.y);
}