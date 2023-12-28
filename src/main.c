/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:12:15 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/28 09:55:25 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
// Pour les masques de mlx_hook :	1L << 0 = KeyPressMask
//									1L << 3 = ButtonRelease (pour la croix)
// Le lien avec tous les masques et events : https://harm-smits.github.io/42docs/libs/minilibx/events.html
int hook_resize(void)
{
	return (0);
}
int	main(int ac, char **av)
{
	t_level		level;
	t_imgdata	img;

	if (ac != 2)
		return (error("Wrong number of arguments"));
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		exit(error("A map <.cub> expected"));
	init(&level);
	parse(av[1], &level);
	init_mlx(&img);
	draw_map(level, img);
	printf("size.x: %d\n", level.data.map_size.x);
	printf("size.y: %d\n", level.data.map_size.y);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_hook(img.win, 2, 1L << 0, key_hooks, &img.mlx);
	mlx_hook(img.win, 17, 1L << 3, close_cub3d, &img.mlx);
	mlx_hook(img.win, 25, 1L << 18, hook_resize, &img.mlx);
	mlx_loop(img.mlx);
	return (0);
}
