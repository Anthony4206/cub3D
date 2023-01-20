/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:21:24 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/10 11:10:14 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../utils.h"
#include "../init.h"
#include "../structs.h"
#include "../parse/parse.h"
#include "walls.h"

//step_x and step_y eather -1 or +1 to indicate the dir of the ray
void	calculate_side_dist(t_ctx *ctx)
{
	if (ctx->ray.ray_dir_x < 0)
	{
		ctx->ray.step_x = -1;
		ctx->ray.side_dist_x = (ctx->player.pos_x - ctx->ray.map_x)
			* ctx->ray.delta_dist_x;
	}
	else
	{
		ctx->ray.step_x = 1;
		ctx->ray.side_dist_x = (ctx->ray.map_x + 1.0 - ctx->player.pos_x)
			* ctx->ray.delta_dist_x;
	}
	if (ctx->ray.ray_dir_y < 0)
	{
		ctx->ray.step_y = -1;
		ctx->ray.side_dist_y = (ctx->player.pos_y - ctx->ray.map_y)
			* ctx->ray.delta_dist_y;
	}
	else
	{
		ctx->ray.step_y = 1;
		ctx->ray.side_dist_y = (ctx->ray.map_y + 1.0 - ctx->player.pos_y)
			* ctx->ray.delta_dist_y;
	}
}

//if side == 1, we bumped a Yline => N or S wall
// if side == 0, a x-line => E or W wall
//we check if the square we bumped into belongs to a wall, if yes, we stop
void	exec_dda(t_ctx *ctx, int x)
{
	bool	hit;

	(void)x;
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
		if (ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] - '0' > 0)
			hit = true;
	}
}

void	calc_height_wall(t_ctx *ctx)
{
	ctx->wall.line_height = (int)(HEIGHT / ctx->ray.perp_wall_dist);
	ctx->wall.draw_start = -ctx->wall.line_height / 2 + HEIGHT / 2;
	if (ctx->wall.draw_start < 0)
		ctx->wall.draw_start = 0;
	ctx->wall.draw_end = ctx->wall.line_height / 2 + HEIGHT / 2;
	if (ctx->wall.draw_end >= HEIGHT)
		ctx->wall.draw_end = HEIGHT - 1;
}

void	calc_delta_dist(t_ctx *ctx)
{
	if (ctx->ray.ray_dir_x == 0)
		ctx->ray.delta_dist_x = 1e30;
	else
		ctx->ray.delta_dist_x = fabs(1 / ctx->ray.ray_dir_x);
	if (ctx->ray.ray_dir_y == 0)
		ctx->ray.delta_dist_y = 1e30;
	else
		ctx->ray.delta_dist_y = fabs(1 / ctx->ray.ray_dir_y);
}

void	raycasting_walls(t_ctx *ctx)
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
		calc_delta_dist(ctx);
		calculate_side_dist(ctx);
		exec_dda(ctx, x);
		if (ctx->ray.hit_side == 0)
			ctx->ray.perp_wall_dist = (ctx->ray.side_dist_x
					- ctx->ray.delta_dist_x);
		else
			ctx->ray.perp_wall_dist = (ctx->ray.side_dist_y
					- ctx->ray.delta_dist_y);
		calc_height_wall(ctx);
		draw_wall(ctx, x);
	}
}
