/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:12:15 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/03 21:41:28 by jsousa-a         ###   ########.fr       */
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
void load_default_texture(t_texture *texture, t_imgdata mlx)
{
	texture[0].path = ft_strdup("textures/texture1.xpm");
	texture[0].img.img = mlx_xpm_file_to_image(mlx.mlx, texture[0].path, &texture[0].width, &texture[0].height);
	if (!texture[0].img.img)
		exit(error("Texture not found"));
	texture[0].img.addr = mlx_get_data_addr(texture[0].img.img, &texture[0].img.bpp, &texture[0].img.len, &texture[0].img.endian);
	texture[1].path = ft_strdup("textures/texture2.xpm");
	texture[1].img.img = mlx_xpm_file_to_image(mlx.mlx, texture[1].path, &texture[1].width, &texture[1].height);
	if (!texture[1].img.img)
		exit(error("Texture not found"));
	texture[1].img.addr = mlx_get_data_addr(texture[1].img.img, &texture[1].img.bpp, &texture[1].img.len, &texture[1].img.endian);
	texture[2].path = ft_strdup("textures/texture3.xpm");
	texture[2].img.img = mlx_xpm_file_to_image(mlx.mlx, texture[2].path, &texture[2].width, &texture[2].height);
	if (!texture[2].img.img)
		exit(error("Texture not found"));
	texture[2].img.addr = mlx_get_data_addr(texture[2].img.img, &texture[2].img.bpp, &texture[2].img.len, &texture[2].img.endian);
	texture[3].path = ft_strdup("textures/texture4.xpm");
	texture[3].img.img = mlx_xpm_file_to_image(mlx.mlx, texture[3].path, &texture[3].width, &texture[3].height);
	if (!texture[3].img.img)
		exit(error("Texture not found"));
	texture[3].img.addr = mlx_get_data_addr(texture[3].img.img, &texture[3].img.bpp, &texture[3].img.len, &texture[3].img.endian);
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
	level = set_fov(level, 110);
	mlx_hook(level.mlx.win, 2, 1L << 0, key_press, &level);
	mlx_hook(level.mlx.win, 3, 1L << 1, key_release, &level);
	mlx_hook(level.mlx.win, 17, 1L << 3, close_cub3d, &level.mlx.mlx);
	mlx_hook(level.mlx.win, 25, 1L << 18, hook_resize, &level);
	mlx_loop_hook(level.mlx.mlx, player_process, &level);
	mlx_loop(level.mlx.mlx);
	return (0);
}
