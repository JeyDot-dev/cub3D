/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:41:35 by jordan            #+#    #+#             */
/*   Updated: 2023/12/29 09:30:23 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum e_state
{
	TEXTURE,
	COLORS,
	MAP,
	ERROR
};

enum e_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_vector_line
{
	t_vector	start;
	t_vector	end;
	int			dy;
	int			dx;
	int			e;
	int			inc[2];
	int			color;
	int			color2;
}	t_vector_line;

typedef struct s_texture
{
	char	*name;
	char	*path;
}	t_texture;

typedef struct	s_imgdata{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_imgdata;

typedef struct s_data
{
	t_vector	file_size;
	t_vector	map_size;
	t_texture	*texture;
	t_texture	*colors;
}	t_data;
typedef struct s_ray
{
	t_vector	ray_dir;
	t_vector	ray_dist;
	t_vector	delta_dist;
	t_vector	step;
	t_vector	cam_plane;
	double		perp_wall_dist;
	int			map[2];
	int			side;
	int			hit;
	int			ray_count;
}				t_ray;
typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	int			fov;
}	t_player;

typedef struct s_level
{
	char		**map;
	char		*name;
	t_data		data;
	t_player	player;
	t_ray		ray;
	t_imgdata	mlx;
}	t_level;

#endif
