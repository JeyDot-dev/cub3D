/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 04:19:22 by lebojo            #+#    #+#             */
/*   Updated: 2024/02/06 16:21:18 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*strdup_exclude_endl(char *src)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = ft_calloc(sizeof(char), ft_strlen(src) + 1);
	while (src[i] != '\0' && src[i] != '\n')
		dest[j++] = src[i++];
	return (dest);
}

int	compare_tag(char *line, char *tag)
{
	int		i;

	i = 0;
	while (line[i] == tag[i] && line[i] && tag[i])
		i++;
	if (tag[i] || line[i])
		return (0);
	return (1);
}

t_texture	add_texture(char *new_texture, t_level *lvl)
{
	t_texture	result;
	char		**tmp;

	tmp = ft_split(new_texture, ' ');
	if (tmp[2] != NULL || !ft_strnstr(tmp[1], ".xpm", ft_strlen(tmp[1]))
		|| (!compare_tag(tmp[0], "NO")
			&& !compare_tag(tmp[0], "SO")
			&& !compare_tag(tmp[0], "WE")
			&& !compare_tag(tmp[0], "EA")))
		clean_exit(lvl, "Invalid texture in map!", 1);
	result.name = strdup_exclude_endl(tmp[0]);
	result.path = strdup_exclude_endl(tmp[1]);
	free_tab(tmp);
	return (result);
}

void	parse(char *file_path, t_level *lvl)
{
	int		file;

	file = open(file_path, O_RDONLY);
	if (file == -1)
		clean_exit(lvl, "Invalid file path!", 1);
	lvl->name = lvl_name_extractor(file_path);
	parse_file(file, lvl);
	close(file);
	if (locate_player(lvl) == 0)
		clean_exit(lvl, "No player in map!", 1);
	if (parse_validity(lvl))
		clean_exit(lvl, "Invalid map!", 1);
}
