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

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	time;
	double	old_time;
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

typedef struct s_wall
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}		t_wall;

typedef struct s_parse
{
	int	map_height;
	int	map_width;
	int	line_map_start;
	char	**map;
	double	init_posX;
	double	init_posY;
	char	init_dir; //NSEW
	//initial malloc
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
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_data;

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
}			t_ctx;

#endif
