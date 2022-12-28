/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:26:26 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/28 10:33:58 by alevasse         ###   ########.fr       */
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
}				t_ray;

typedef struct s_wall
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}			t_wall;

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

#endif