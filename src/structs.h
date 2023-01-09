/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:26:26 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/09 11:29:43 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define WIDTH 900
# define HEIGHT 600

# include <stdio.h>
#include <stdbool.h>

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
}			t_player;

typedef struct s_ray
{
	double	cameraX;
	double	ray_dirX;
	double	ray_dirY;
	double	plane_X;
	double	plane_Y;
	double	delta_distX;
	double	delta_distY;
	double	side_distX;
	double	side_distY;
	int		stepX;
	int		stepY;
	int		mapX;
	int		mapY;
	int		hit_side;
	double	perp_wall_dist;
}			t_ray;

typedef struct s_tex
{
	int		tex_width;
	int		tex_height;
	int		**texture; //tab of all textures, containing texHeight*texWidth
	int		tex_num;
	double	wallX;
	int		texX;
	int		texY;
}		t_tex;

typedef struct s_wall
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}		t_wall;

//A REMPLIR AVEC DES DONNEES DU PARSE
typedef struct s_map
{
	int		height;
	int		width;
}			t_map;

typedef struct s_parse
{
	int	map_height;
	int	map_width;
	int	line_map_start;
	char	**map;
	double	init_posX;
	double	init_posY;
	char	init_dir; //NSEW
	char	*N;
	char	*S;
	char	*E;
	char	*W;
	char	*F;
	int		F_RGB;
	char	*C;
	int		C_RGB;
}		t_parse;


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

typedef struct s_screen
{
	int				width; //in pixel
	int				height; //in pixel
	unsigned int	**buffer;
}					t_screen;

typedef struct s_texture
{
    t_data	N_wall;
    t_data	S_wall;
    t_data	E_wall;
    t_data	W_wall;
}   		t_texture;

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
    t_texture   texture;
	t_tex		tex;
}			t_ctx;

#endif
