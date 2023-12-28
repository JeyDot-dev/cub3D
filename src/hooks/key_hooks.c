/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:37:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/28 09:55:42 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

int	key_hooks(int keycode)
{
	if (keycode == 65307 || keycode == 53)
		close_cub3d();
	else if ((keycode > 65360 && keycode < 65365) ||
			(keycode > 122 && keycode < 127))
		ft_fprintf(2, "left, right, up, down\n");
	else if (keycode == 65453 || keycode == 65451 ||
			keycode == 69 || keycode == 78)
		ft_fprintf(2, "+-\n");
	else if ((keycode > 47 && keycode < 52) || 
			(keycode > 17 && keycode < 30))
		ft_fprintf(2, "1, 2, 3, 4, 5, 6, 7, 8, 9, 0\n");
	return (0);
}

int	close_cub3d(void)
{
//	delete_list(mlx->pts);
//	mlx_destroy_image(mlx->mlx, mlx->img.img);
//	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}
