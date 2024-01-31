/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:12:15 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/31 15:51:28 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_level	set_cam_plane(t_level level)
{
	level.ray.cam_plane.x = level.player.dir.y * tan(110 / 2 * M_PI / 180);
	level.ray.cam_plane.y = level.player.dir.x * tan(110 / 2 * M_PI / 180);
	return (level);
}

void	load_default_texture(int max_texture, t_texture *texture, t_imgdata mlx)
{
	int	i;

	i = 0;
	while (i < max_texture)
	{
		texture[i].img.img = mlx_xpm_file_to_image(mlx.mlx, texture[i].path,
				&texture[i].width, &texture[i].height);
		if (texture[i].img.img == NULL)
			printf(YEL"[WARNING] "RESET"Texture: \"%s not found\"\n",
				texture[i].path);
		else
			texture[i].img.addr = mlx_get_data_addr(texture[i].img.img,
					&texture[i].img.bpp, &texture[i].img.len,
					&texture[i].img.endian);
		i++;
	}
}

int	mouse_move(int x, int y, t_level *lvl)
{
	int		speed;
	int		vert_speed;

	if (x == WIN_WIDTH / 2 && y == GAME_HEIGHT / 2)
	{
		lvl->mouse = 0;
		return (0);
	}
	lvl->mouse = 1;
	speed = (x - (WIN_WIDTH / 2)) / 5;
	vert_speed = (y - (GAME_HEIGHT / 2)) / 3;
	lvl->player.dir = rotate_vector(lvl->player.dir, speed);
	lvl->ray.cam_plane = rotate_vector(lvl->ray.cam_plane, speed);
	lvl->player.vert_dir -= vert_speed;
	if (lvl->player.vert_dir > 250)
		lvl->player.vert_dir = 250;
	else if (lvl->player.vert_dir < -250)
		lvl->player.vert_dir = -250;
	mlx_mouse_move(lvl->mlx.win, WIN_WIDTH / 2, GAME_HEIGHT / 2);
	return (0);
}

int	main(int ac, char **av)
{
	t_level		level;

	if (ac != 2)
		return (error("Wrong number of arguments"));
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		exit(error("A map <.cub> expected"));
	init_mlx(&level.mlx);
	init(&level);
	parse(av[1], &level);
	load_default_texture(level.data.max_texture, level.data.texture, level.mlx);
	level = set_cam_plane(level);
	mlx_hook(level.mlx.win, 2, 1L << 0, key_press, &level);
	mlx_hook(level.mlx.win, 3, 1L << 1, key_release, &level);
	mlx_hook(level.mlx.win, 17, 1L << 3, close_cub3d, &level);
	mlx_mouse_hide();
	mlx_hook(level.mlx.win, 6, 1L << 6, mouse_move, &level);
	mlx_loop_hook(level.mlx.mlx, player_process, &level);
	mlx_loop(level.mlx.mlx);
	return (0);
}
