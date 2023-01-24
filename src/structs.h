/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:26:26 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 16:04:44 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define WIDTH 900
# define HEIGHT 700
# include <stdio.h>
# include <mlx.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}			t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	plane_x;
	double	plane_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		hit_side;
	double	perp_wall_dist;
}			t_ray;

typedef struct s_data
{
	void	*img;
	int		tex_width;
	int		tex_height;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_data;

typedef struct s_tex
{
	t_data	select_tex;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	int		tex_y;
}		t_tex;

typedef struct s_wall
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_data	texture;
}		t_wall;

typedef struct s_map
{
	int		height;
	int		width;
}			t_map;

typedef struct s_parse
{
	int		map_height;
	int		map_width;
	int		line_map_start;
	char	**map;
	double	init_pos_x;
	double	init_pos_y;
	char	init_dir;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*floor;
	int		f_rgb;
	char	*ceiling;
	int		c_rgb;
}		t_parse;

/*W and H in pixels. */
typedef struct s_screen
{
	int				width;
	int				height;
	unsigned int	**buffer;
}					t_screen;

typedef struct s_texture
{
	t_data	n_wall;
	t_data	s_wall;
	t_data	e_wall;
	t_data	w_wall;
}			t_texture;

typedef struct s_keys
{
	bool	key_w;
	bool	key_a;
	bool	key_s;
	bool	key_d;
	bool	key_left;
	bool	key_right;
}			t_keys;

typedef struct s_ctx
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_parse		parse;
	t_map		map;
	t_wall		wall;
	t_ray		ray;
	t_player	player;
	t_screen	screen;
	t_texture	texture;
	t_tex		tex;
	t_keys		keys;
}			t_ctx;

#endif
