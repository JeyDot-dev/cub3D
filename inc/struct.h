/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:41:35 by jordan            #+#    #+#             */
/*   Updated: 2023/12/21 17:27:28 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_data
{
	t_vector	size;
}	t_data;

typedef struct s_level
{
	char		*map_raw;
	char		**map;
	t_data		data;
	t_vector	size;
}	t_level;

#endif