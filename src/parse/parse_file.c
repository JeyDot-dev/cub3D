/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:59:51 by lebojo            #+#    #+#             */
/*   Updated: 2024/02/06 18:12:38 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**clean_parse_color(char *tmp, t_level *lvl)
{
	char	**res;
	char	**no_space;
	char	*tmp2;
	int		i;

	no_space = ft_split(tmp, ' ');
	if (no_space[1] == NULL)
	{
		free_tab(no_space);
		clean_exit(lvl, "Invalid color in map!", 1);
	}
	tmp2 = ft_strdup(no_space[1]);
	i = 0;
	if (no_space[2] != NULL)
	{
		while (no_space[++i + 1])
			tmp2 = add_str(tmp2, no_space[i + 1], 1);
	}
	res = ft_split(tmp2, ',');
	free(tmp2);
	free_tab(no_space);
	return (res);
}

void	parse_color(char *tmp, t_data *data, char type, t_level *lvl)
{
	char	**tmp2;
	int		w;

	tmp = strdup_exclude_endl(tmp);
	tmp2 = clean_parse_color(tmp, lvl);
	w = 0;
	if (type == 'F')
		data->floor = rgbo_color(ft_atoi(tmp2[0]),
				ft_atoi(tmp2[1]), ft_atoi(tmp2[2]), 0);
	else if (type == 'C')
		data->ceiling = rgbo_color(ft_atoi(tmp2[0]),
				ft_atoi(tmp2[1]), ft_atoi(tmp2[2]), 0);
	else
		w = 1;
	free(tmp);
	free_tab(tmp2);
	if (w)
		clean_exit(lvl, "Invalid color in map!", 1);
}

void	parse_file_map(char *tmp, t_level *lvl, int *fat_one)
{
	lvl->map = add_tab(lvl->map, tmp);
	if ((int)ft_strlen(tmp) > *fat_one)
		*fat_one = ft_strlen(tmp);
	lvl->data.map_size = vector2d(*fat_one, ++lvl->data.map_size.y);
}

int	parse_texture(t_data *data, char *line, int state, t_level *lvl)
{
	if (state || !ft_strchr("FCNSEW", line[0]))
		return (1);
	if (check_textures_and_colors(*data, line))
		clean_exit(lvl, "Double texture in map!", 1);
	if (line[0] == 'F' || line[0] == 'C')
		parse_color(line, data, line[0], lvl);
	else if (line[0] == 'N' && data->texture[0].name == NULL)
		data->texture[0] = add_texture(line, lvl);
	else if (line[0] == 'S' && data->texture[1].name == NULL)
		data->texture[1] = add_texture(line, lvl);
	else if (line[0] == 'W' && data->texture[2].name == NULL)
		data->texture[2] = add_texture(line, lvl);
	else if (line[0] == 'E' && data->texture[3].name == NULL)
		data->texture[3] = add_texture(line, lvl);
	else
		return (1);
	return (0);
}

int	parse_file(int file, t_level *lvl)
{
	char	*tmp;
	int		fat_one;
	int		state;

	tmp = get_next_line(file);
	fat_one = 0;
	while (tmp)
	{
		if (tmp[0] != '\n' && tmp[0] != '\0')
		{
			state = parse_texture(&lvl->data, tmp, state, lvl);
			if (state)
				parse_file_map(tmp, lvl, &fat_one);
		}
		if ((tmp[0] == '\n' || tmp[0] == '\0') && state)
			clean_exit(lvl, "Invalid map!", 1);
		free(tmp);
		tmp = get_next_line(file);
	}
	return (info("Raw parsed"));
}
