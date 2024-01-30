/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 04:19:22 by lebojo            #+#    #+#             */
/*   Updated: 2024/01/30 18:21:46 by lebojo           ###   ########.fr       */
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

t_texture	*add_texture(t_level *lvl, char *new_texture)
{
	t_texture	new;
	t_texture	*new_tab;
	char		**tmp;
	int			i;

	tmp = ft_split(new_texture, ' ');
	new.name = strdup_exclude_endl(tmp[0]);
	new.path = strdup_exclude_endl(tmp[1]);
	free_tab(tmp);
	i = 0;
	while (lvl->data.texture[i].name)
		i++;
	new_tab = malloc(sizeof(t_texture) * (i + 2));
	i = 0;
	while (lvl->data.texture[i].name)
	{
		new_tab[i] = lvl->data.texture[i];
		i++;
	}
	new_tab[i] = new;
	new_tab[i + 1].name = NULL;
	free(lvl->data.texture);
	lvl->data.max_texture = i;
	return (new_tab);
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
}
