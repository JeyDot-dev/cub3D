/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 04:19:22 by lebojo            #+#    #+#             */
/*   Updated: 2024/01/10 17:19:38 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	file_char_len(char *file_path)
{
	int		file;
	int		i;
	char	buffer;

	file = open(file_path, O_RDONLY);
	i = 0;
	if (file == -1)
		return (0);
	while (read(file, &buffer, sizeof(char)) != 0)
		i++;
	close(file);
	return (i);
}

enum e_state	state_incrementer(enum e_state s, int sz)
{
	if (sz > 1)
		return (s);
	if (s == TEXTURE)
		return (COLORS);
	else if (s == COLORS)
		return (MAP);
	return (ERROR);
}

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

char	**add_tab(char **src, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (src && src[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (src && src[i])
	{
		new_tab[i] = strdup_exclude_endl(src[i]);
		i++;
	}
	new_tab[i++] = strdup_exclude_endl(str);
	new_tab[i] = NULL;
	if (src)
		free_tab(src);
	return (new_tab);
}

t_texture	*add_texture(t_texture *src, char *new_texture)
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
	while (src[i].name)
		i++;
	new_tab = malloc(sizeof(t_texture) * (i + 2));
	i = 0;
	while (src[i].name)
	{
		new_tab[i] = src[i];
		i++;
	}
	new_tab[i] = new;
	new_tab[i + 1].name = NULL;
	free(src);
	return (new_tab);
}

int	parse_file(int file, t_level *lvl)
{
	char			*tmp;
	int				sz;
	int				fat_one;
	enum e_state	state;

	info("Parsing map");
	state = TEXTURE;
	tmp = get_next_line(file);
	fat_one = 0;
	while (tmp)
	{
		sz = ft_strlen(tmp);
		state = state_incrementer(state, sz);
		if (tmp[0] != '\n')
		{
			if (state == TEXTURE)
				lvl->data.texture = add_texture(lvl->data.texture, tmp);
			else if (state == COLORS)
			{
				tmp = strdup_exclude_endl(tmp);
				char	**tmp3 = ft_split(tmp, ' ');
				char	**tmp2 = ft_split(tmp3[1], ',');
				lvl->data.ceiling = rgbo_color(ft_atoi(tmp2[0]),
						ft_atoi(tmp2[1]), ft_atoi(tmp2[2]), 0);
				free(tmp);
				tmp = get_next_line(file);
				tmp = strdup_exclude_endl(tmp);
				tmp3 = ft_split(tmp, ' ');
				tmp2 = ft_split(tmp3[1], ',');
				lvl->data.floor = rgbo_color(ft_atoi(tmp2[0]),
						ft_atoi(tmp2[1]), ft_atoi(tmp2[2]), 0);
				free_tab(tmp2);
				free_tab(tmp3);
			}
			else if (state == MAP)
			{
				lvl->map = add_tab(lvl->map, tmp);
				if (sz > fat_one)
					fat_one = sz;
				lvl->data.map_size = vector2D(fat_one, ++lvl->data.map_size.y);
			}
			else
				return (error("Invalid map"));
		}
		free(tmp);
		tmp = get_next_line(file);
	}
	return (info("Raw parsed"));
}

void	parse(char *file_path, t_level *lvl)
{
	int		file;

	lvl->name = lvl_name_extractor(file_path);
	file = open(file_path, O_RDONLY);
	if (file == -1)
		return ;
	parse_file(file, lvl); //On met la map dans un char*
	close(file);
}
