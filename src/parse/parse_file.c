/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:59:51 by lebojo            #+#    #+#             */
/*   Updated: 2024/01/31 15:14:46 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_color(char *tmp, t_data *data, char type)
{
	char	**tmp2;
	char	**tmp3;

	tmp = strdup_exclude_endl(tmp);
	tmp3 = ft_split(tmp, ' ');
	tmp2 = ft_split(tmp3[1], ',');
	if (type == 'F')
		data->floor = rgbo_color(ft_atoi(tmp2[0]),
				ft_atoi(tmp2[1]), ft_atoi(tmp2[2]), 0);
	else if (type == 'C')
		data->ceiling = rgbo_color(ft_atoi(tmp2[0]),
				ft_atoi(tmp2[1]), ft_atoi(tmp2[2]), 0);
	else
		exit(error("Invalid color in map!"));
	free(tmp);
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

int	parse_texture(t_data *data, char *line, int state)
{
	if (state || !ft_strchr("FCNSEW", line[0]))
		return (1);
	if (check_textures_and_colors(*data, line))
		exit (error("Double texture in map!"));
	if (line[0] == 'F' || line[0] == 'C')
		parse_color(line, data, line[0]);
	else if (line[0] == 'N' && data->texture[0].name == NULL)
		data->texture[0] = add_texture(line);
	else if (line[0] == 'S' && data->texture[1].name == NULL)
		data->texture[1] = add_texture(line);
	else if (line[0] == 'W' && data->texture[2].name == NULL)
		data->texture[2] = add_texture(line);
	else if (line[0] == 'E' && data->texture[3].name == NULL)
		data->texture[3] = add_texture(line);
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
			state = parse_texture(&lvl->data, tmp, state);
			if (state)
				parse_file_map(tmp, lvl, fat_one);
		}
		free(tmp);
		tmp = get_next_line(file);
	}
	return (info("Raw parsed"));
}
