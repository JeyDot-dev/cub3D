/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 04:19:22 by lebojo            #+#    #+#             */
/*   Updated: 2023/12/22 00:05:47 by jordan           ###   ########.fr       */
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

enum e_state state_incrementer(enum e_state s, int sz)
{
	if (sz > 1)
		return (s);
	if (s == TEXTURE)
		return (COLORS);
	else if (s == COLORS)
		return (MAP);
	return (ERROR);
}

char	**add_tab(char **src, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (src[i])
	{
		new_tab[i] = ft_strdup(src[i]);
		i++;
	}
	new_tab[i++] = ft_strdup(str);
	new_tab[i] = NULL;
	free_tab(src);
	return (new_tab);
}

t_texture *add_texture(t_texture *src, char *new_texture)
{
	t_texture	new;
	t_texture	*new_tab;
	char		**tmp;
	int			i;

	tmp = ft_split(new_texture, ' ');
	new.name = ft_strdup(tmp[0]);
	new.path = ft_strdup(tmp[1]);
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
	enum e_state	state;

	info("Parsing map");
	state = TEXTURE;
	tmp = get_next_line(file);
	while (tmp)
	{
		sz = ft_strlen(tmp);
		state = state_incrementer(state, sz);
		if (sz > 1)
		{
			if (state == TEXTURE)
				lvl->data.texture = add_texture(lvl->data.texture, tmp);
			else if (state == COLORS)
				lvl->data.colors = parse_texture(lvl->data.colors, tmp);
			else if (state == MAP)
				lvl->map = add_tab(lvl->map, tmp);
			else
				return (error("Invalid map"));
		}
		free(tmp);
		tmp = get_next_line(file);
	}
	info("Raw parsed");
}

void	parse(char *file_path, t_level *lvl)
{
	int		file;

	if (check_ext(file_path, ".cub") == 0)
		exit(error("A map <.cub> expected"));
	lvl->name = lvl_name_extractor(file_path);
	file = open(file_path, O_RDONLY);
	if (file == -1)
		return ;
	parse_file(file, lvl); //On met la map dans un char*
	close(file);
}
