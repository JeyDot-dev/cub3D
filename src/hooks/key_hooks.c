/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:37:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/30 18:36:57 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_level *lvl)
{
	lvl->player.input[int_to_dir(keycode)] = 1;
	if (keycode == 65307 || keycode == 53)
		close_cub3d();
	return (0);
}

int	key_release(int keycode, t_level *lvl)
{
	lvl->player.input[int_to_dir(keycode)] = 0;
	return (0);
}

int	close_cub3d(void)
{
	exit(0);
}
