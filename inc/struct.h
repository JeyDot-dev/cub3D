/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:41:35 by jordan            #+#    #+#             */
/*   Updated: 2024/02/06 04:21:26 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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

typedef struct s_imgdata
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_imgdata;

typedef struct s_texture
{
	char		*name;
	char		*path;
	t_imgdata	img;
	int			start_x;
	int			pos_x;
	int			pos_y;
	int			width;
	int			height;
}	t_texture;

typedef struct s_data
{
	t_vector	file_size;
	t_vector	map_size;
	t_texture	texture[4];
	int			ceiling;
	int			floor;
	int			max_texture;
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

typedef struct s_minimap
{
	char	*player[8];
	char	*empty;
	char	*wall;
	char	*floor;
	void	*blck;
}	t_minimap;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	int			vert_dir;
	int			input[9];
	float		rot_speed;
	t_vector	vel;
	float		speed;
	float		max_speed;
}	t_player;

typedef struct s_level
{
	char		**map;
	char		*name;
	int			mouse;
	int			rev_ctrl;
	t_data		data;
	t_player	player;
	t_ray		ray;
	t_imgdata	mlx;
	t_minimap	minmap;
}	t_level;

#endif
