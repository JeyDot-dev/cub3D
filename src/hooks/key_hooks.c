/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:37:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/02 17:33:00 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_level *lvl)
{
	lvl->player.input[int_to_dir(keycode)] = 1;
	if (keycode == 65307 || keycode == 53)
		close_cub3d();
	// else if ((keycode > 65360 && keycode < 65365) ||
	// 		(keycode > 122 && keycode < 127))
	// 	player_move_and_rotate(lvl, keycode % 65360);
	// else if (keycode == 65453 || keycode == 65451 ||
	// 		keycode == 69 || keycode == 78)
	// 	ft_fprintf(2, "+-\n");
	// else if ((keycode > 47 && keycode < 52) || 
	// 		(keycode > 17 && keycode < 30))
	// 	ft_fprintf(2, "1, 2, 3, 4, 5, 6, 7, 8, 9, 0\n");
	return (0);
}

int	key_release(int keycode, t_level *lvl)
{
	lvl->player.input[int_to_dir(keycode)] = 0;
	return (0);
}

int	close_cub3d(void)
{
//	delete_list(mlx->pts);
//	mlx_destroy_image(mlx->mlx, mlx->img.img);
//	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}
