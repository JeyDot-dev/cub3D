/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:58:02 by jordan            #+#    #+#             */
/*   Updated: 2024/01/30 17:43:08 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector	vector2d(double x, double y)
{
	t_vector	res;

	res.x = x;
	res.y = y;
	return (res);
}

void	set_vector2d(t_vector *vector, double x, double y)
{
	*vector = vector2d(x, y);
}

int	vector_equal(t_vector a, t_vector b)
{
	if (a.x == b.x && a.y == b.y)
		return (1);
	return (0);
}
