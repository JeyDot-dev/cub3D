/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:12:15 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/29 10:04:09 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
// Pour les masques de mlx_hook :	1L << 0 = KeyPressMask
//									1L << 3 = ButtonRelease (pour la croix)
// Le lien avec tous les masques et events : https://harm-smits.github.io/42docs/libs/minilibx/events.html
t_vector rotate_vector(t_vector v, double angle)
{
    t_vector	result;
	float		radian; 
    float		cos_a; 
    float		sin_a;

	radian = angle * M_PI / 180.0;
	cos_a = cos(radian);
	sin_a = sin(radian);

    result.x = v.x * cos_a - v.y * sin_a;
    result.y = v.x * sin_a + v.y * cos_a;

    return result;
}
void erase_img(t_imgdata *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			draw_pixel(img, j, i, 0x000000);
			j++;
		}
		i++;
	}
}
t_ray map_ray_and_dir(t_player p, t_ray r)
{
	double	camera_x;

	camera_x = 2 * r.ray_count / (double)WIN_WIDTH - 1;
	r.ray_dir.x = p.dir.x + r.cam_plane.x * camera_x;
	r.ray_dir.y = p.dir.y + r.cam_plane.y * camera_x;
	return (r);
}

t_vector calculate_delta_dist(t_ray r)
{
	t_vector	delta_dist;

	if (r.ray_dir.y == 0)
		r.ray_dir.y = 1e30;
	else
		delta_dist.y = fabs(1 / r.ray_dir.y);
	if (r.ray_dir.x == 0)
		r.ray_dir.x = 1e30;
	else
		delta_dist.x = fabs(1 / r.ray_dir.x);
	return (delta_dist);
}

t_ray calculate_initial_dist(t_player p, t_ray r)
{
	if (r.ray_dir.x < 0)
	{
		r.step.x = -1;
		r.ray_dist.x = (p.pos.x - r.map[0]) * r.delta_dist.x;
	}
	else
	{
		r.step.x = 1;
		r.ray_dist.x = (r.map[0] + 1.0 - p.pos.x) * r.delta_dist.x;
	}
	if (r.ray_dir.y < 0)
	{
		r.step.y = -1;
		r.ray_dist.y = (p.pos.y - r.map[1]) * r.delta_dist.y;
	}
	else
	{
		r.step.y = 1;
		r.ray_dist.y = (r.map[1] + 1.0 - p.pos.y) * r.delta_dist.y;
	}
	return (r);
}

t_ray digital_differential_analysis(t_ray r, char **map)
{
	while (r.hit == 0)
	{
		if (r.ray_dist.x < r.ray_dist.y)
		{
			r.ray_dist.x += r.delta_dist.x;
			r.map[0] += (int) r.step.x;
			r.side = 0;
		}
		else
		{
			r.ray_dist.y += r.delta_dist.y;
			r.map[1] += (int) r.step.y;
			r.side = 1;
		}
		if (map[r.map[1]][r.map[0]] == '1')
			r.hit = 1;
	}
	return (r);
}
void	draw_vertical_line(t_imgdata *img, int x, int y[2], int color)
{
	int	i;

	i = y[0];
	while (i < y[1])
	{
		draw_pixel(img, x, i, color);
		i++;
	}
}
void	draw_ray(t_imgdata *img, t_ray r, char **map)
{
	int	y[2];
	int	color;

	y[0] = (int) -(WIN_HEIGHT / r.perp_wall_dist) / 2 + WIN_HEIGHT / 2;
	if (y[0] < 0)
		y[0] = 0;
	y[1] = (int) (WIN_HEIGHT / r.perp_wall_dist) / 2 + WIN_HEIGHT / 2;
	if (y[1] >= WIN_HEIGHT)
		y[1] = WIN_HEIGHT - 1;
	if (map[r.map[1]][r.map[0]] == '1')
	{
		color = rgbo_color(120, 160, 70, 0);
	}
	else
		color = 0x0000FF;
	if (r.side == 1)
		color = color / 2;
	draw_vertical_line(img, r.ray_count, y, color);

}
double calculate_perp_wall_distance(t_ray r)
{
	double	perp_wall_dist;

	if (r.side == 0)
		perp_wall_dist = r.ray_dist.x - r.delta_dist.x;
	else
		perp_wall_dist = r.ray_dist.y - r.delta_dist.y;
	return (perp_wall_dist);
}

int	ray_caster(t_level level, t_imgdata *img)
{
	printf("RAY CASTER pos: %f, %f\n", level.player.pos.x, level.player.pos.y);
	t_ray		ray;
	
	ray = level.ray;
	level.ray.ray_count = 0;
	erase_img(img);
	while (ray.ray_count < WIN_WIDTH)
	{
		ray.hit = 0;
		printf("ray_count: %d\n", ray.ray_count);
		ray.map[0] = (int) level.player.pos.x;
		ray.map[1] = (int) level.player.pos.y;
		ray = map_ray_and_dir(level.player, ray);
		ray.delta_dist = calculate_delta_dist(ray);
		ray = calculate_initial_dist(level.player, ray);
		ray = digital_differential_analysis(ray, level.map);
		ray.perp_wall_dist = calculate_perp_wall_distance(ray);
		draw_ray(img, ray, level.map);
		ray.ray_count++;
	}
	printf("RAY CASTER END pos: %f, %f\n", level.player.pos.x, level.player.pos.y);
	return (0);
}

t_level default_position(t_level level, double fov)
{
	level.player.pos.x = 9;
	level.player.pos.y = 4;
	level.player.dir.x = 0.6;
	level.player.dir.y = 0.4;
	level.player.fov = fov;
	level.ray.cam_plane.x = level.player.dir.y * tan(fov / 2 * M_PI / 180);
	level.ray.cam_plane.y = level.player.dir.x * tan(fov / 2 * M_PI / 180);
	return (level);

}

int hook_resize(void)
{
	return (0);
}
void	print_map(char **map, t_player player)
{
	int	i;
	int	j;

	i = 0;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == (int)player.pos.y && j == (int)player.pos.x)
				printf("P");
			else
				printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void move_test(t_level *level, int key)
{
	double	move_speed;
	int		rot_speed;

	move_speed = 0.1;
	rot_speed = 10;
	printf("player dir: %f, %f\n", level->player.dir.x, level->player.dir.y);
	if (key == 2)
	{
		if (level->map[(int)(level->player.pos.x + level->player.dir.x * move_speed)][(int)level->player.pos.y] == '0')
			level->player.pos.x += level->player.dir.x * move_speed;
		if (level->map[(int)level->player.pos.x][(int)(level->player.pos.y + level->player.dir.y * move_speed)] == '0')
			level->player.pos.y += level->player.dir.y * move_speed;
	}
	else if (key == 4)
	{
		if (level->map[(int)(level->player.pos.x - level->player.dir.x * move_speed)][(int)level->player.pos.y] == '0')
			level->player.pos.x -= level->player.dir.x * move_speed;
		if (level->map[(int)level->player.pos.x][(int)(level->player.pos.y - level->player.dir.y * move_speed)] == '0')
			level->player.pos.y -= level->player.dir.y * move_speed;
	}
	else if (key == 1)
	{
		level->player.dir = rotate_vector(level->player.dir, -rot_speed);
		level->ray.cam_plane = rotate_vector(level->ray.cam_plane, -rot_speed);
	}
	else if (key == 3)
	{
		level->player.dir = rotate_vector(level->player.dir, rot_speed);
		level->ray.cam_plane = rotate_vector(level->ray.cam_plane, rot_speed);
	}
	printf("player dir post rot: %f, %f\n", level->player.dir.x, level->player.dir.y);
	printf("MOVE pos: %f, %f\n", level->player.pos.x, level->player.pos.y);
	ray_caster(*level, &level->mlx);
	mlx_put_image_to_window(level->mlx.mlx, level->mlx.win, level->mlx.img, 0, 0);
}

int	key_hooks(int keycode, t_level *level)
{
	if (keycode == 65307 || keycode == 53)
		close_cub3d();
	else if ((keycode > 65360 && keycode < 65365) ||
			(keycode > 122 && keycode < 127))
		move_test(level, keycode % 65360);
	else if (keycode == 65453 || keycode == 65451 ||
			keycode == 69 || keycode == 78)
		ft_fprintf(2, "+-\n");
	else if ((keycode > 47 && keycode < 52) || 
			(keycode > 17 && keycode < 30))
		ft_fprintf(2, "1, 2, 3, 4, 5, 6, 7, 8, 9, 0\n");
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
	level = default_position(level, 66);
	print_map(level.map, level.player);
	ray_caster(level, &level.mlx);
	mlx_put_image_to_window(level.mlx.mlx, level.mlx.win, level.mlx.img, 0, 0);
	mlx_hook(level.mlx.win, 2, 1L << 0, key_hooks, &level);
	mlx_hook(level.mlx.win, 17, 1L << 3, close_cub3d, &level.mlx.mlx);
	mlx_hook(level.mlx.win, 25, 1L << 18, hook_resize, &level);
	mlx_loop(level.mlx.mlx);
	return (0);
}
