/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:12:15 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/10 14:41:36 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
// Pour les masques de mlx_hook :	1L << 0 = KeyPressMask
//									1L << 3 = ButtonRelease (pour la croix)
// Le lien avec tous les masques et events : 
// https://harm-smits.github.io/42docs/libs/minilibx/events.html
//  	 ---pour le moment je la garde ici car elle initialise 
//  	|	une position de base pour le joueur
// 		v

t_level	set_cam_plane(t_level level)
{
	level.player.pos.x = 9;
	level.player.pos.y = 4;
	level.player.dir.x = -1;
	level.player.dir.y = 0;
	level.ray.cam_plane.x = level.player.dir.y * tan(110 / 2 * M_PI / 180);
	level.ray.cam_plane.y = level.player.dir.x * tan(110 / 2 * M_PI / 180);
	return (level);
}

void	load_default_texture(t_texture *texture, t_imgdata mlx)
{
	int	i;
//TODO: Change while i < 4 to while i < max_texture
	i = 0;
	while (i < 4)
	{
		texture[i].img.img = mlx_xpm_file_to_image(mlx.mlx, texture[i].path,
				&texture[i].width, &texture[i].height);
		if (texture[i].img.img == NULL)
			printf(YEL"[WARNING] "RESET"Texture: \"%s not found\"\n",
					texture[i].path);
		else
			texture[i].img.addr = mlx_get_data_addr(texture[i].img.img, &texture[i].img.bpp, &texture[i].img.len, &texture[i].img.endian);
		i++;
	}
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
	load_default_texture(level.data.texture, level.mlx);
	level = set_cam_plane(level);
	mlx_hook(level.mlx.win, 2, 1L << 0, key_press, &level);
	mlx_hook(level.mlx.win, 3, 1L << 1, key_release, &level);
	mlx_hook(level.mlx.win, 17, 1L << 3, close_cub3d, &level.mlx.mlx);
	mlx_hook(level.mlx.win, 25, 1L << 18, hook_resize, &level);
	mlx_loop_hook(level.mlx.mlx, player_process, &level);
	mlx_loop(level.mlx.mlx);
	return (0);
}
