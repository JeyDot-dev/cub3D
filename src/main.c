/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:12:15 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/27 18:06:25 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

int	main(int ac, char **av)
{
	t_level		level;
	t_imgdata	img;

	if (ac != 2)
		return (error("Wrong number of arguments"));
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		return (error("Wrong file extension"));
	init(&level);
	parse(av[1], &level);
	init_mlx(&img);
	draw_map(level, img);
	printf("size.x: %d\n", level.data.map_size.x);
	printf("size.y: %d\n", level.data.map_size.y);
	printf("name: %s\n", level.name);
	printf("texture[0].name: %s\n", level.data.texture[0].name);
	printf("texture[0].path: %s\n", level.data.texture[0].path);
	printf("map[0]: %s\n", level.map[0]);
	printf("map[0]: %s\n", level.map[13]);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_loop(img.mlx);
	return (0);
}
