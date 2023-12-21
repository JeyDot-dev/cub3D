/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 04:19:22 by lebojo            #+#    #+#             */
/*   Updated: 2023/12/21 18:42:24 by jordan           ###   ########.fr       */
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

void	parse_raw(int file, t_level *lvl)
{
	int		i;
	int		line_size;
	char	buffer;

	i = 0;
	line_size = 0;
	info("Parsing raw map");
	while (read(file, &buffer, sizeof(char)) != 0)
	{
		lvl->map_raw[i++] = buffer;
		line_size++;
		if (buffer == '\n')
		{
			if (lvl->data.size.x < line_size)
				lvl->data.size.x = line_size; // La on get la taille de la plus longue ligne
			lvl->data.size.y++;
			line_size = 0;
		}
	}
	lvl->map_raw[i] = '\0';
	info("Raw map parsed");
}

void	parse_map(t_level *lvl)
{
	t_vector	index;
	int			i;

	index = vector2D(0, 0);
	i = -1;
	lvl->map = ft_calloc(lvl->data.size.y + 2, sizeof(char *));
	while (index.y <= lvl->data.size.y)
	{
		lvl->map[index.y] = malloc(sizeof(char) * lvl->data.size.x + 1);
		lvl->map[index.y][index.x] = '\0';
		index.x = -1;
		while (++index.x < lvl->data.size.x && lvl->map_raw[++i] != '\n')
		{
			lvl->map[index.y][index.x] = lvl->map_raw[i];
		}
		printf("%i, %s\n", index.y, lvl->map[index.y]);
		index.y++;
	}
	lvl->map[index.y] = NULL;
}

void	parse(char *file_path, t_level *lvl)
{
	int		file;

	if (check_ext(file_path, ".cub") == 0)
		exit(error("A map <.cub> expected"));
	lvl->map_raw = malloc(sizeof(char) * file_char_len(file_path));
	lvl->name = lvl_name_extractor(file_path);
	file = open(file_path, O_RDONLY);
	if (file == -1)
		return ;
	parse_raw(file, lvl); //On met la map dans un char*
	close(file);
	parse_map(lvl); //On met la map dans un char**, pour pouvoir y acceder avec des coordonnees
}
