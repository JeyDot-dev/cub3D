/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:58:02 by jordan            #+#    #+#             */
/*   Updated: 2023/12/21 17:59:27 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector vector2D(int x, int y)
{
	t_vector res;

	res.x = x;
	res.y = y;
	return (res);
}

void set_vector2D(t_vector *vector, int x, int y)
{
	*vector = vector2D(x, y);
}