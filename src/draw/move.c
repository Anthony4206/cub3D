/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:32:33 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/20 13:32:35 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../structs.h"
#include "walls.h"

int	player_low_perim_is_clear(t_ctx *ctx, float x, float y, int r)
{
	while (x < ctx->player.pos_x)
	{
		x += 0.000001;
		y += 0.000001;
		if (ctx->parse.map[(int)y][(int)x] - '0' > 0)
			return (0);
	}
	while (x < ctx->player.pos_x + r)
	{
		x += 0.000001;
		y -= 0.000001;
		if (ctx->parse.map[(int)y][(int)x] - '0' > 0)
			return (0);
	}
	return (1);
}

int	check_new_pos(t_ctx *ctx)
{
	double	r;
	float	x;
	float	y;

	r = 0.2;
	x = ctx->player.pos_x + r;
	y = ctx->player.pos_y;
	while (x > ctx->player.pos_x)
	{
		x -= 0.000001;
		y -= 0.000001;
		if (ctx->parse.map[(int)y][(int)x] - '0' > 0)
			return (0);
	}
	while (x > ctx->player.pos_x - r)
	{
		x -= 0.000001;
		y += 0.000001;
		if (ctx->parse.map[(int)y][(int)x] - '0' > 0)
			return (0);
	}
	if (!player_low_perim_is_clear(ctx, x, y, r))
		return (0);
	return (1);
}

void	change_pos(t_ctx *ctx, float a, float b)
{
	ctx->player.pos_x = ctx->player.pos_x + a;
	ctx->player.pos_y = ctx->player.pos_y + b;
}

void	player_moves(t_ctx *ctx)
{
	float	step;
	float	old_pos_x;
	float	old_pos_y;

	step = 0.08;
	old_pos_x = ctx->player.pos_x;
	old_pos_y = ctx->player.pos_y;
	if (ctx->keys.key_w == true)
		change_pos(ctx, ctx->player.dir_x * step, ctx->player.dir_y * step);
	else if (ctx->keys.key_s == true)
		change_pos(ctx, -ctx->player.dir_x * step, -ctx->player.dir_y * step);
	else if (ctx->keys.key_d == true)
		change_pos(ctx, -ctx->player.dir_y * step, ctx->player.dir_x * step);
	else if (ctx->keys.key_a == true)
		change_pos(ctx, ctx->player.dir_y * step, -ctx->player.dir_x * step);
	if (!check_new_pos(ctx))
	{
		ctx->player.pos_x = old_pos_x;
		ctx->player.pos_y = old_pos_y;
		if (!(sliding_ag_walls(ctx, step)))
		{
			ctx->player.pos_x = old_pos_x;
			ctx->player.pos_y = old_pos_y;
		}
	}
}

void	player_rotates(t_ctx *ctx)
{
	float	a;
	double	tmp_x;
	double	tmp_plane_x;

	a = 0;
	if (ctx->keys.key_left == true)
		a = -0.05;
	else if (ctx->keys.key_right == true)
		a = 0.05;
	if (ctx->keys.key_left == true || ctx->keys.key_right == true)
	{
		tmp_x = ctx->player.dir_x * cos(a) + ctx->player.dir_y * (-sin(a));
		ctx->player.dir_y = ctx->player.dir_x * sin(a) + ctx->player.dir_y
			* (cos(a));
		ctx->player.dir_x = tmp_x;
		tmp_plane_x = ctx->ray.plane_x * cos(a) - ctx->ray.plane_y * sin(a);
		ctx->ray.plane_y = ctx->ray.plane_x * sin(a) + ctx->ray.plane_y
			* cos(a);
		ctx->ray.plane_x = tmp_plane_x;
	}
}
