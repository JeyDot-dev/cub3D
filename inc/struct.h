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

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_texture
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*Floor;
	char	*Ceiling;
}	t_texture;

typedef struct s_data
{
	t_vector	size;
	t_texture	texture;
}	t_data;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
}	t_player;

typedef struct s_level
{
	char		*map_raw;
	char		**map;
	char		*name;
	t_data		data;
	t_player	player;
}	t_level;

#endif