/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:12:15 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/02 16:48:41 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
// Pour les masques de mlx_hook :	1L << 0 = KeyPressMask
//									1L << 3 = ButtonRelease (pour la croix)
// Le lien avec tous les masques et events : https://harm-smits.github.io/42docs/libs/minilibx/events.html

//  	 ---pour le moment je la garde ici car elle initialise une position de base pour le joueur,
// 		|	une fois le parsing termine a 100% cette fonction sera exclusivement utilisee pour regler le FOV
// 		v
t_level set_fov(t_level level, double fov)
{
	level.player.pos.x = 9;
	level.player.pos.y = 4;
	level.player.dir.x = -1;
	level.player.dir.y = 0;
	level.player.fov = fov;
	level.ray.cam_plane.x = level.player.dir.y * tan(fov / 2 * M_PI / 180);
	level.ray.cam_plane.y = level.player.dir.x * tan(fov / 2 * M_PI / 180);
	return (level);

}

int hook_resize(void)
{
	return (0);
}


int	main(int ac, char **av)
{
	t_level		level;

	if (ac != 2)
		return (error("Wrong number of arguments"));
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		exit(error("A map <.cub> expected"));
	init(&level);
	parse(av[1], &level);
	init_mlx(&level.mlx);
	level = set_fov(level, 110);
	//terminal_mini_map(level.map, level);
	ray_caster(level, &level.mlx);
	mlx_put_image_to_window(level.mlx.mlx, level.mlx.win, level.mlx.img, 0, 0);
	mlx_hook(level.mlx.win, 2, 1L << 0, key_press, &level);
	mlx_hook(level.mlx.win, 3, 1L << 1, key_release, &level);
	mlx_hook(level.mlx.win, 17, 1L << 3, close_cub3d, &level.mlx.mlx);
	mlx_hook(level.mlx.win, 25, 1L << 18, hook_resize, &level);
	mlx_loop_hook(level.mlx.mlx, minimap_process, &level);
	mlx_loop(level.mlx.mlx);
	return (0);
}
