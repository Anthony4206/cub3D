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
#include "../utils_bonus.h"
#include "../init_bonus.h"
#include "../structs_bonus.h"
#include "../parse/parse_bonus.h"
#include "walls_bonus.h"

//stepX and StepY eather -1 or +1 to indicate the dir of the ray
void	calculate_side_dist(t_ctx *ctx)
{
	if (ctx->ray.ray_dirX < 0)
	{
		ctx->ray.stepX = -1;
		ctx->ray.side_distX = (ctx->player.posX - ctx->ray.mapX) * ctx->ray.delta_distX;
	}
	else
	{
		ctx->ray.stepX = 1;
		ctx->ray.side_distX = (ctx->ray.mapX + 1.0 - ctx->player.posX) * ctx->ray.delta_distX;
	}
	if (ctx->ray.ray_dirY < 0)
	{
		ctx->ray.stepY = -1;
		ctx->ray.side_distY = (ctx->player.posY - ctx->ray.mapY) * ctx->ray.delta_distY;	
	}
	else
	{
		ctx->ray.stepY = 1;
		ctx->ray.side_distY = (ctx->ray.mapY + 1.0 - ctx->player.posY) * ctx->ray.delta_distY;
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
		if (ctx->ray.side_distX < ctx->ray.side_distY)
		{
			ctx->ray.side_distX += ctx->ray.delta_distX;
			ctx->ray.mapX += ctx->ray.stepX;
			ctx->ray.hit_side = 0;
		}
		else
		{
			ctx->ray.side_distY += ctx->ray.delta_distY;
			ctx->ray.mapY += ctx->ray.stepY;
			ctx->ray.hit_side = 1;			
		}
		if (ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] == '1' ||
            ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] == 'D' )
			hit = true;
        if (ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] == 'D')
            ctx->wall.is_door = 1;
        else
            ctx->wall.is_door = 0;
	}
}

void	calc_perp_wall_dist(t_ctx *ctx)
{
	if (ctx->ray.hit_side == 0)
		ctx->ray.perp_wall_dist = (ctx->ray.side_distX - ctx->ray.delta_distX);
	else
		ctx->ray.perp_wall_dist = (ctx->ray.side_distY - ctx->ray.delta_distY);
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

void	raycasting_walls(t_ctx *ctx)
{
	int	x;
	
	x = -1;
	while (++x < WIDTH)
	{
		ctx->ray.cameraX = 2 * x / (double)WIDTH - 1;
		ctx->ray.ray_dirX = ctx->player.dirX + ctx->ray.plane_X * ctx->ray.cameraX;
		ctx->ray.ray_dirY = ctx->player.dirY + ctx->ray.plane_Y * ctx->ray.cameraX;
		ctx->ray.mapX = (int)ctx->player.posX;
		ctx->ray.mapY = (int)ctx->player.posY;
		if (ctx->ray.ray_dirX == 0)
			ctx->ray.delta_distX = 1e30;
		else
			ctx->ray.delta_distX = fabs(1 / ctx->ray.ray_dirX);
		if (ctx->ray.ray_dirY == 0)
			ctx->ray.delta_distY = 1e30;
		else
			ctx->ray.delta_distY = fabs(1 / ctx->ray.ray_dirY);
		calculate_side_dist(ctx);
		exec_dda(ctx, x);
		calc_perp_wall_dist(ctx);
		calc_height_wall(ctx);
		draw_wall(ctx, x);
	}
}
