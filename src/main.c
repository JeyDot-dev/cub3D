/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:12:15 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/27 16:12:13 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void	draw_square(t_vector origin, t_imgdata *img, char c)
{
	int	color;
	int	x;
	int	y;

	if (c == '1')
		color = rgbo_color(180, 65, 158, 0);
	else if (c == '0')
		color = rgbo_color(80, 108, 90, 0);
	x = origin.x * 20;
	y = origin.y * 20;
	while (x < origin.x + 20)
	{
		while (y < origin.y + 20)
		{
			draw_pixel(img->img, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_map(t_level level, t_imgdata img)
{
	t_vector	origin;
	int			x;
	int			y;

	origin.x = 0;
	origin.y = 0;
	while (origin.y < level.data.map_size.y)
	{
		while (origin.x < level.data.map_size.x)
		{
			if (level.map[origin.y][origin.x] == '1')
				draw_square(origin, img.img, '1');
			else if (level.map[y][x] == '0')
				draw_square(origin, img.img, '0');
			x++;
		}
		x = 0;
		y++;
	}
}

t_vector_line	make_line(int x, int y, int x2, int y2, t_imgdata *img)
{
	t_vector_line	line;

	line.start.x = x;
	line.start.y = y;
	line.end.x = x2;
	line.end.y = y2;
	line.color = 0x00FF0000;
	line.color2 = 0x0000FF00;
	draw_line(img->img, line);
	return (line);
}

void	init_mlx(t_imgdata *img)
{
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, 1240, 720, "test");
	img->img = mlx_new_image(img->mlx, 1240, 720);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->endian);
}

int	main(int ac, char **av)
{
	t_level		level;
//	t_imgdata	img;


	if (ac != 2)
		return (error("Wrong number of arguments"));
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		return (error("Wrong file extension"));
	init(&level);
	parse(av[1], &level);
//	init_mlx(&img);
//	draw_map(level, img);
	printf("size.x: %d\n", level.data.map_size.x);
	printf("size.y: %d\n", level.data.map_size.y);
	printf("name: %s\n", level.name);

	printf("texture[0].name: %s\n", level.data.texture[0].name);
	printf("texture[0].path: %s\n", level.data.texture[0].path);
	printf("map[0]: %s\n", level.map[0]);
	printf("map[0]: %s\n", level.map[13]);
	return (0);
}
