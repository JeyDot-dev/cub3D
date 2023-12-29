/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:53:43 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/29 17:01:56 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

double calculate_perp_wall_distance(t_ray r)
{
	double	perp_wall_dist;

	if (r.side == 0)
		perp_wall_dist = r.ray_dist.x - r.delta_dist.x;
	else
		perp_wall_dist = r.ray_dist.y - r.delta_dist.y;
	return (perp_wall_dist);
}

void ray_caster(t_level level, t_imgdata *img)
{
	t_ray		ray;
	
	ray = level.ray;
	level.ray.ray_count = 0;
	erase_img(img);
	while (ray.ray_count < WIN_WIDTH)
	{
		ray.hit = 0;
		ray.map[0] = (int) level.player.pos.x;
		ray.map[1] = (int) level.player.pos.y;
		ray = map_ray_and_dir(level.player, ray);
		ray.delta_dist = calculate_delta_dist(ray);
		ray = calculate_initial_dist(level.player, ray);
		ray = dda(ray, level.map);
		ray.perp_wall_dist = calculate_perp_wall_distance(ray);
		draw_ray(img, ray, level.map);
		ray.ray_count++;
	}
}
