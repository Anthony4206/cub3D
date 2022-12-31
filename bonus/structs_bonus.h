/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:26:26 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/29 15:13:57 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*********
 * Struct bonus
 * ***********/

typedef struct s_sprite
{
    double  x;
    double  y;
    int     texture;
}       t_sprite;

/**********************/

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	time;
	double	old_time;
}			t_player;

typedef struct s_ray
{
	double	cameraX;
	double	ray_dirX;
	double	ray_dirY;
}			t_ray;

typedef struct s_background
{
    float   ray_dirX0;
    float   ray_dirY0;
    float   ray_dirX1;
    float   ray_dirY1;
    int     pos;
    float   posZ;
    float   row_distance;
    float   floor_stepX;
    float   floor_stepY;
    int     floorX;
    int     floorY;
    int     cellX;
    int     cellY;
    int     tx;
    int     ty;
    int     floor_tex;
    int     cell_tex;
    Uint32  color;
}			t_background;

typedef struct s_wall
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}		t_wall;

typedef struct s_map
{
	int		mapX;
	int		mapY;
	double	side_distX;
	double	side_distY;
	double	delta_distX;
	double	delta_distY;
	double	perp_wall_dist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
}			t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_data;

typedef struct s_ctx
{
	void		    *mlx;
	void		    *win;
	t_data		    img;
	t_map		    map;
	t_wall		    wall;
	t_ray		    ray;
	t_player	    player;
    t_background    bg;
}			        t_ctx;

#endif
