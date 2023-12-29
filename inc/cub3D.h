/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:30:47 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/12/29 10:17:15 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define	CUB3D_H
# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include <struct.h>
# include <color.h>

# define NAME "Apex: double legends 2 - live edition"
# define NAME_SHORT "ADL2LE"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

/*	CONSOLE					*/
int		error(char *str);
int		info(char *str);

/*	INIT						*/
void	init(t_level *level);
void	init_mlx(t_imgdata *img);

/*	VECTOR					*/
t_vector	vector2D(int x, int y);
void		set_vector2D(t_vector *vector, int x, int y);


/* FREE						*/
void		free_tab(char **tab);

/*	PARSE/PARSE_UTILS		*/
char	*add_str(char *s1, char *s2, int f);
char	*lvl_name_extractor(char *s);

/*	PARSE/PARSE_VALIDITY		*/
// int		check_req(t_requierements r);
// int		check_cell_exist(t_data d, char c);
// void	new_line_check(t_level *l, t_vector pos, int i);
// void	cell_checker(t_level *l, t_vector *pos, t_requierements *req, int i);
// int		parse_validity(t_level lvl);

/*	PARSE					*/
void	parse(char *file_path, t_level *lvl);

/*	HOOKS					*/
//int		key_hooks(int keycode);
int		close_cub3d(void);
/*	DRAW/			*/
void	draw_line(t_imgdata *img, t_vector_line line);
void	draw_pixel(t_imgdata *img, int x, int y, int color);
void	draw_map(t_level level, t_imgdata img);
void	draw_square(t_vector origin, t_imgdata img, char c);
/*	COLOR/			*/
int		rgbo_color(int r, int g, int b, int o);
int		min_max_value(int color);
int		smooth_colors(int color, int target_color, int pixels);
int		r_value(int color);
int		g_value(int color);
int		b_value(int color);
int		o_value(int color);
#endif
