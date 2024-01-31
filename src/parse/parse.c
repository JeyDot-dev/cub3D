/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 04:19:22 by lebojo            #+#    #+#             */
/*   Updated: 2024/01/31 14:57:59 by lebojo           ###   ########.fr       */
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
		printf("line: %s, tag: %s\n", line, tag);
	return (1);
}

t_texture	add_texture(char *new_texture)
{
	t_texture	result;
	char		**tmp;

	tmp = ft_split(new_texture, ' ');
	if (tmp[2] != NULL || !ft_strnstr(tmp[1], ".xpm", ft_strlen(tmp[1]))
		|| (!compare_tag(tmp[0], "NO")
			&& !compare_tag(tmp[0], "SO")
			&& !compare_tag(tmp[0], "WE")
			&& !compare_tag(tmp[0], "EA")))
		exit(error("Invalid texture in map!"));
	result.name = strdup_exclude_endl(tmp[0]);
	result.path = strdup_exclude_endl(tmp[1]);
	free_tab(tmp);
	return (result);
}

void	parse(char *file_path, t_level *lvl)
{
	int		file;

	lvl->name = lvl_name_extractor(file_path);
	file = open(file_path, O_RDONLY);
	if (file == -1)
		return ;
	parse_file(file, lvl);
	close(file);
	if (locate_player(lvl) == 0)
		exit(error("No player found"));
	if (parse_validity(lvl))
		exit(error("Map is not valid"));
}
