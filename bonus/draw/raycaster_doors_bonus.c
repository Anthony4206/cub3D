/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_doors_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:14:13 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 15:24:21 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs_bonus.h"
#include "walls_bonus.h"

void	color_x_stripe_door(t_ctx *ctx, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	step = 1.0 * ctx->tex.select_tex.tex_height / ctx->wall.line_height;
	tex_pos = (ctx->wall.draw_start - HEIGHT / 2
			+ ctx->wall.line_height / 2) * step;
	y = ctx->wall.draw_start - 1;
	while (++y < ctx->wall.draw_end)
	{
		ctx->tex.tex_y = (int)tex_pos & (ctx->tex.select_tex.tex_height - 1);
		tex_pos += step;
		color = (*(int *)(ctx->tex.select_tex.addr + (4
						* ctx->tex.select_tex.tex_width * (int)ctx->tex.tex_y)
					+ (4 * (int)ctx->tex.tex_x)));
		my_mlx_pixel_put(&ctx->img_door, x, y, color);
	}
	if (ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == '1' ||
		ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == 'D' ||
		(ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == 'O' &&
		color == 0x261B1B))
		ctx->sprites.z_buffer[x] = ctx->ray.perp_wall_dist;
}

int	pos_door(char **map, int x, int y)
{
	if (map[y + 1][x] == 'D' || map[y - 1][x] == 'D' || map[y][x + 1] == 'D' ||
		map[y][x - 1] == 'D' || map[y + 1][x] == 'O' || map[y - 1][x] == 'O' ||
		map[y][x + 1] == 'O' || map[y][x - 1] == 'O')
	{
		if (map[y + 1][x] == 'D')
			map[y + 1][x] = 'O';
		else if (map[y + 1][x] == 'O')
			map[y + 1][x] = 'D';
		if (map[y - 1][x] == 'D')
			map[y - 1][x] = 'O';
		else if (map[y - 1][x] == 'O')
			map[y - 1][x] = 'D';
		if (map[y][x + 1] == 'D')
			map[y][x + 1] = 'O';
		else if (map[y][x + 1] == 'O')
			map[y][x + 1] = 'D';
		if (map[y][x - 1] == 'D')
			map[y][x - 1] = 'O';
		else if (map[y][x - 1] == 'O')
			map[y][x - 1] = 'D';
		return (1);
	}
	return (0);
}

void	init_tex_door(t_ctx *ctx)
{
	if (ctx->parse.map_door[ctx->ray.map_y][ctx->ray.map_x])
	{
		ctx->tex.select_tex = ctx->texture.tex_door[4];
		if (ctx->keys.key_door
			&& pos_door(ctx->parse.map, ctx->player.pos_x, ctx->player.pos_y))
			ctx->keys.key_door = false;
	}
	else
	{
		ctx->tex.select_tex = ctx->texture.tex_door[0];
		if (ctx->keys.key_door
			&& pos_door(ctx->parse.map, ctx->player.pos_x, ctx->player.pos_y))
			ctx->keys.key_door = false;
	}
}

void	draw_door(t_ctx *ctx, int x)
{
	init_tex_door(ctx);
	calc_wall_x(ctx);
	calc_x_coord_tex(ctx);
	color_x_stripe_door(ctx, x);
}

int	exec_dda_door(t_ctx *ctx)
{
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (ctx->ray.side_dist_x < ctx->ray.side_dist_y)
		{
			ctx->ray.side_dist_x += ctx->ray.delta_dist_x;
			ctx->ray.map_x += ctx->ray.step_x;
			ctx->ray.hit_side = 0;
		}
		else
		{
			ctx->ray.side_dist_y += ctx->ray.delta_dist_y;
			ctx->ray.map_y += ctx->ray.step_y;
			ctx->ray.hit_side = 1;
		}
		if (ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == '1')
		{
			hit = true;
			return (0);
		}
		else if (ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == 'D')
		{
			hit = true;
			ctx->parse.map_door[ctx->ray.map_y][ctx->ray.map_x] = 1;
		}
		else if (ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == 'O')
		{
			hit = true;
			ctx->parse.map_door[ctx->ray.map_y][ctx->ray.map_x] = 0;
		}
	}
	return (1);
}

void	raycasting_doors(t_ctx *ctx)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		ctx->ray.camera_x = 2 * x / (double)WIDTH - 1;
		ctx->ray.ray_dir_x = ctx->player.dir_x + ctx->ray.plane_x * ctx->ray.camera_x;
		ctx->ray.ray_dir_y = ctx->player.dir_y + ctx->ray.plane_y * ctx->ray.camera_x;
		ctx->ray.map_x = (int)ctx->player.pos_x;
		ctx->ray.map_y = (int)ctx->player.pos_y;
		if (ctx->ray.ray_dir_x == 0)
			ctx->ray.delta_dist_x = 1e30;
		else
			ctx->ray.delta_dist_x = fabs(1 / ctx->ray.ray_dir_x);
		if (ctx->ray.ray_dir_y == 0)
			ctx->ray.delta_dist_y = 1e30;
		else
			ctx->ray.delta_dist_y = fabs(1 / ctx->ray.ray_dir_y);
		calculate_side_dist(ctx);
		if (!exec_dda_door(ctx))
			continue ;
		calc_perp_wall_dist(ctx);
		calc_height_wall(ctx);
		draw_door(ctx, x);
	}
}
