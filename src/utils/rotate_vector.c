/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:39:10 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/10 15:23:38 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector	rotate_vector(t_vector v, double angle)
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
	return (result);
}
