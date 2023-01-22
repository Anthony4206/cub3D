/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:26:26 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 14:39:55 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# define WIDTH 900
# define HEIGHT 700
# define M_WIDTH 350
# define M_HEIGHT 350

# include <mlx.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include <sys/stat.h>

typedef struct s_coord
{
	double	x;
	double	y;
}			t_coord;

typedef struct s_time
{
	int	init_time;
}			t_time;

typedef struct s_sprites
{
	int		num;
	double	*z_buffer;
	int		*order;
	double	*sprite_distance;
	double	sprite_x;
	double	sprite_y;
	t_coord	*sprite;
	int		screen_x;
	int		height;
	int		width;
	int		draw_start_y;
	int		draw_start_x;
	int		draw_end_y;
	int		draw_end_x;
	double	trans_x;
	double	trans_y;
	int		tex_x;
	int		selec_tex;
	char	**sprite_path;
}			t_sprites;

typedef struct s_mouse
{
	int	save_x;
	int	mouse_pressed;
}		t_mouse;

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

typedef struct s_minimap
{
	t_data	mini_map;
}			t_minimap;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
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

typedef struct s_tex
{
	t_data	select_tex;
	double	wall_x;
	int		tex_x;
	int		tex_y;
}			t_tex;

typedef struct s_wall
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_data	texture;
}			t_wall;

typedef struct s_parse
{
	int		map_height;
	int		map_width;
	int		line_map_start;
	char	**map;
	int		**map_door;
	double	init_pos_x;
	double	init_pos_y;
	char	init_dir;
	char	*n;
	char	*s;
	char	*e;
	char	*w;
	char	*f;
	int		f_rgb;
	char	*c;
	int		c_rgb;
	int		sprites_num;
}		t_parse;

typedef struct s_screen
{
	unsigned int	**buffer;
}					t_screen;

typedef struct s_texture
{
	t_data	n_wall;
	t_data	s_wall;
	t_data	e_wall;
	t_data	w_wall;
	t_data	tex_door[5];
	t_data	*sprites;
}			t_texture;

typedef struct s_keys
{
	bool	key_w;
	bool	key_a;
	bool	key_s;
	bool	key_d;
	bool	key_left;
	bool	key_right;
	bool	key_door;
}			t_keys;

typedef struct s_ctx
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_data		img_door;
	t_data		img_sprite;
	t_parse		parse;
	t_wall		wall;
	t_ray		ray;
	t_player	player;
	t_screen	screen;
	t_texture	texture;
	t_tex		tex;
	t_keys		keys;
	t_sprites	sprites;
	t_mouse		mouse;
	t_minimap	mini;
	t_time		time;
}				t_ctx;

#endif
