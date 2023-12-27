/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:41:35 by jordan            #+#    #+#             */
/*   Updated: 2023/12/21 22:25:26 by jordan           ###   ########.fr       */
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

typedef struct s_vector
{
	int	x;
	int	y;
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

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
}	t_player;

typedef struct s_level
{
	char		**map;
	char		*name;
	t_data		data;
	t_player	player;
}	t_level;

#endif
