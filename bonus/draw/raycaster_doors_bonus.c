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
#include "draw_bonus.h"

int	check_for_walls_doors(t_ctx *ctx, bool *hit)
{
	if (ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == '1')
	{
		*hit = true;
		return (0);
	}
	else if (ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == 'D')
	{
		*hit = true;
		ctx->parse.map_door[ctx->ray.map_y][ctx->ray.map_x] = 1;
	}
	else if (ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == 'O')
	{
		*hit = true;
		ctx->parse.map_door[ctx->ray.map_y][ctx->ray.map_x] = 0;
	}
	return (1);
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
		if (!check_for_walls_doors(ctx, &hit))
			return (0);
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
		ctx->ray.ray_dir_x = ctx->player.dir_x + ctx->ray.plane_x
			* ctx->ray.camera_x;
		ctx->ray.ray_dir_y = ctx->player.dir_y + ctx->ray.plane_y
			* ctx->ray.camera_x;
		ctx->ray.map_x = (int)ctx->player.pos_x;
		ctx->ray.map_y = (int)ctx->player.pos_y;
		calculate_delta(ctx);
		calculate_side_dist(ctx);
		if (!exec_dda_door(ctx))
			continue ;
		calc_perp_wall_dist(ctx);
		calc_height_wall(ctx);
		draw_door(ctx, x);
	}
}
