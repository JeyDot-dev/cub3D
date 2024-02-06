/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:26:04 by jordan            #+#    #+#             */
/*   Updated: 2024/02/06 17:58:34 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

char	*add_str(char *s1, char *s2, int f)
{
	char	*res;
	int		i;
	int		ii;

	res = malloc(ft_strlen(s1) + ft_strlen(s2) + sizeof(char));
	i = -1;
	ii = 0;
	while (s1[++i])
		res[i] = s1[i];
	while (s2[ii])
		res[i++] = s2[ii++];
	res[i] = '\0';
	if (f == 1)
		free(s1);
	else if (f == 2)
		free(s2);
	else if (f == 3)
	{
		free(s1);
		free(s2);
	}
	return (res);
}

char	*lvl_name_extractor(char *s)
{
	int		i;
	char	*res;

	i = 0;
	while (*s != '/' && *s)
		s++;
	s++;
	while (s[i] != '.' && s[i])
		i++;
	res = malloc(sizeof(char) * i);
	i = -1;
	while (s[++i] != '.' && s[i])
		res[i] = s[i];
	return (res);
}

int	set_player_pos(t_level *lvl, int j, int i)
{
	lvl->player.pos = vector2d(j + 0.5, i + 0.5);
	if (lvl->map[i][j] == 'N')
		lvl->player.dir = vector2d(-0.0, -1.0);
	else if (lvl->map[i][j] == 'S')
		lvl->player.dir = vector2d(0, 1);
	else if (lvl->map[i][j] == 'E')
		lvl->player.dir = vector2d(1, 0);
	else if (lvl->map[i][j] == 'W')
		lvl->player.dir = vector2d(-1, 0);
	if (lvl->map[i][j] == 'N' || lvl->map[i][j] == 'S')
		lvl->rev_ctrl = -1;
	return (1);
}

int	locate_player(t_level *lvl)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (lvl->map[i])
	{
		j = 0;
		while (lvl->map[i][j])
		{
			if (ft_strchr("NSEW", lvl->map[i][j]))
			{
				if (lvl->player.pos.x != 0 || lvl->player.pos.y != 0)
					clean_exit(lvl, "Multiple player in map!", 1);
				set_player_pos(lvl, j, i);
			}
			j++;
		}
		i++;
	}
	if (lvl->player.pos.x != 0 && lvl->player.pos.y != 0)
		return (1);
	return (0);
}
