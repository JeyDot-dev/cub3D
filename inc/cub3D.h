/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:30:47 by jsousa-a          #+#    #+#             */
/*   Updated: 2024/01/05 16:05:37 by jsousa-a         ###   ########.fr       */
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

# define NAME "Le RealEngine 2: The first"
# define NAME_SHORT "RE2:TF"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define GAME_HEIGHT 600

/*	CONSOLE					*/
int		error(char *str);
int		info(char *str);
/*	SETUP_TEXTURE	*/
int			pick_cardinal_texture(t_ray r, int max_texture);
t_texture	set_up_texture(t_level lvl, t_ray r, t_vector pos);
/*	RAY_CASTER				*/
void	ray_caster(t_level lvl, t_imgdata *img);

/*	DIGITAL_DIFFERENTIAL_ANALYZER	*/
t_ray	dda(t_ray r, char **map);

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

/*	MOVEMENT	*/
void	rotate_player(t_level *lvl, int rot_speed);
//		 v cette fonction est temporaire v
void	player_move_and_rotate(t_level *lvl, int key);

/*	HOOKS					*/
int		key_press(int keycode, t_level *lvl);
int		key_release(int keycode, t_level *lvl);
int		close_cub3d(void);

/*	HOOKS/LOOP				*/
int 	player_process(t_level *lvl);
int		int_to_dir(int key);
void	move_forward(t_level *lvl);
void	move_backward(t_level *lvl);

/*	DRAW/			*/
void	draw_line(t_imgdata *img, t_vector_line line);
void	draw_pixel(t_imgdata *img, int x, int y, int color);
void	draw_map(t_level level, t_imgdata img);
void	draw_square(t_vector origin, t_imgdata img, char c);
void	draw_ray(t_imgdata *img, t_ray r, t_level lvl);
void	background(t_imgdata *img, int ground, int sky, int pitch);

/*	COLOR/			*/
int		rgbo_color(int r, int g, int b, int o);
int		min_max_value(int color);
int		smooth_colors(int color, int target_color, int pixels);
int		r_value(int color);
int		g_value(int color);
int		b_value(int color);
int		o_value(int color);

/*	UTILS/			*/
void	terminal_mini_map(char **map, t_level lvl);
t_vector	rotate_vector(t_vector vector, double angle);
void	erase_img(t_imgdata *img);

/*	MINIMAP			*/
int	minimap_process(t_level *lvl);
#endif
