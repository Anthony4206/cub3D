/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:32:33 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/23 16:03:47 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../structs_bonus.h"
#include "draw_bonus.h"

int	player_low_perim_is_clear(t_ctx *ctx, double x, double y, int r)
{
	while (x < ctx->player.pos_x)
	{
		x += 0.000001;
		y += 0.000001;
		if (get_texture(ctx, x, y))
			return (0);
	}
	while (x < ctx->player.pos_x + r)
	{
		x += 0.000001;
		y -= 0.000001;
		if (get_texture(ctx, x, y))
			return (0);
	}
	return (1);
}

int	check_new_pos(t_ctx *ctx)
{
	double	r;
	double	x;
	double	y;

	r = 0.2;
	x = ctx->player.pos_x + r;
	y = ctx->player.pos_y;
	while (x > ctx->player.pos_x)
	{
		x -= 0.000001;
		y -= 0.000001;
		if (get_texture(ctx, x, y))
			return (0);
	}
	while (x > ctx->player.pos_x - r)
	{
		x -= 0.000001;
		y += 0.000001;
		if (get_texture(ctx, x, y))
			return (0);
	}
	if (!player_low_perim_is_clear(ctx, x, y, r))
		return (0);
	return (1);
}

void	check_pos_and_slide(t_ctx *ctx, float old_x, float old_y, float step)
{
	if (!check_new_pos(ctx))
	{
		ctx->player.pos_x = old_x;
		ctx->player.pos_y = old_y;
		if (!(sliding_ag_walls(ctx, step)))
		{
			ctx->player.pos_x = old_x;
			ctx->player.pos_y = old_y;
		}
	}
}

void	player_moves(t_ctx *ctx)
{
	float	step;
	float	old_x;
	float	old_y;

	step = 0.15;
	old_x = ctx->player.pos_x;
	old_y = ctx->player.pos_y;
	if (ctx->keys.key_w == true)
		change_pos(ctx, ctx->player.dir_x * step, ctx->player.dir_y * step);
	if (ctx->keys.key_s == true)
		change_pos(ctx, -ctx->player.dir_x * step, -ctx->player.dir_y * step);
	if (ctx->keys.key_d == true && (ctx->parse.init_dir == 'S'
			|| ctx->parse.init_dir == 'W'))
		change_pos(ctx, ctx->player.dir_y * step, -ctx->player.dir_x * step);
	else if (ctx->keys.key_d == true)
		change_pos(ctx, -ctx->player.dir_y * step, ctx->player.dir_x * step);
	if (ctx->keys.key_a == true && (ctx->parse.init_dir == 'S'
			|| ctx->parse.init_dir == 'W'))
		change_pos(ctx, -ctx->player.dir_y * step, ctx->player.dir_x * step);
	else if (ctx->keys.key_a == true)
		change_pos(ctx, ctx->player.dir_y * step, -ctx->player.dir_x * step);
	check_pos_and_slide(ctx, old_x, old_y, step);
}

void	player_rotates(t_ctx *ctx)
{
	float	a;
	double	tmp_x;
	double	tmp_plane_x;

	a = 0;
	if ((ctx->keys.key_left == true && (ctx->parse.init_dir == 'N'
				|| ctx->parse.init_dir == 'E')) || (ctx->keys.key_right == true
			&& (ctx->parse.init_dir == 'S' || ctx->parse.init_dir == 'W')))
		a = -0.05;
	if ((ctx->keys.key_right == true && (ctx->parse.init_dir == 'N'
				|| ctx->parse.init_dir == 'E')) || (ctx->keys.key_left == true
			&& (ctx->parse.init_dir == 'S' || ctx->parse.init_dir == 'W')))
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
