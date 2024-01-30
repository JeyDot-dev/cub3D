/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:59:51 by lebojo            #+#    #+#             */
/*   Updated: 2024/01/30 21:38:39 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

enum e_state	state_incrementer(enum e_state s, int sz)
{
	static int	once = 0;

	if (sz > 1)
	{
		once = 0;
		return (s);
	}
	if (sz <= 1 && once == 1)
		return (s);
	if (sz <= 1)
		once = 1;
	if (s == TEXTURE && once == 1)
		return (COLORS);
	else if (s == COLORS && once == 1)
	{
		info("parsing map");
		return (MAP);
	}
	return (ERROR);
}

void	parse_color(char *tmp, t_level *lvl, int file)
{
	char	**tmp2;
	char	**tmp3;

	tmp = strdup_exclude_endl(tmp);
	tmp3 = ft_split(tmp, ' ');
	tmp2 = ft_split(tmp3[1], ',');
	lvl->data.floor = rgbo_color(ft_atoi(tmp2[0]),
			ft_atoi(tmp2[1]), ft_atoi(tmp2[2]), 0);
	free(tmp);
	tmp = get_next_line(file);
	tmp = strdup_exclude_endl(tmp);
	tmp3 = ft_split(tmp, ' ');
	tmp2 = ft_split(tmp3[1], ',');
	lvl->data.ceiling = rgbo_color(ft_atoi(tmp2[0]),
			ft_atoi(tmp2[1]), ft_atoi(tmp2[2]), 0);
	free_tab(tmp2);
	free_tab(tmp3);
}

void	parse_file_map(char *tmp, t_level *lvl, int fat_one)
{
	lvl->map = add_tab(lvl->map, tmp);
	if ((int)ft_strlen(tmp) > fat_one)
		fat_one = ft_strlen(tmp);
	lvl->data.map_size = vector2d(fat_one, ++lvl->data.map_size.y);
}

int	parse_file(int file, t_level *lvl)
{
	char			*tmp;
	int				fat_one;
	enum e_state	state;

	state = TEXTURE;
	tmp = get_next_line(file);
	fat_one = 0;
	while (tmp)
	{
		state = state_incrementer(state, ft_strlen(tmp));
		if (tmp[0] != '\n' && tmp[0] != '\0')
		{
			if (state == TEXTURE)
				lvl->data.texture = add_texture(lvl, tmp);
			else if (state == COLORS)
				parse_color(tmp, lvl, file);
			else if (state == MAP)
				parse_file_map(tmp, lvl, fat_one);
			else
				return (error("Invalid map"));
		}
		free(tmp);
		tmp = get_next_line(file);
	}
	return (info("Raw parsed"));
}
