/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:18:59 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 15:19:01 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../structs_bonus.h"
#include "walls_bonus.h"

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
		if (ctx->parse.map[(int)y][(int)x] == '1'
		|| ctx->parse.map[(int)y][(int)x] == 'D'
		|| ctx->parse.map[(int)y][(int)x] == 'A')
			return (0);
	}
	while (x > ctx->player.pos_x - r)
	{
		x -= 0.000001;
		y += 0.000001;
		if (ctx->parse.map[(int)y][(int)x] == '1'
		|| ctx->parse.map[(int)y][(int)x] == 'D'
		|| ctx->parse.map[(int)y][(int)x] == 'A')
			return (0);
	}
		while (x < ctx->player.pos_x)
	{
		x += 0.000001;
		y += 0.000001;
		if (ctx->parse.map[(int)y][(int)x] == '1'
		|| ctx->parse.map[(int)y][(int)x] == 'D'
		|| ctx->parse.map[(int)y][(int)x] == 'A')
			return (0);
	}
	while (x < ctx->player.pos_x + r)
	{
		x += 0.000001;
		y -= 0.000001;
		if (ctx->parse.map[(int)y][(int)x] == '1'
		|| ctx->parse.map[(int)y][(int)x] == 'D'
		|| ctx->parse.map[(int)y][(int)x] == 'A')
			return (0);
	}
	return (1);
}

int	check_sliding_ag_walls(t_ctx *ctx, float step)
{
	if (ctx->keys.key_w == true)
	{
		if (ctx->player.dir_x == 0 || ctx->player.dir_y == 0)
			return (0);
		if (ctx->player.dir_x < 0 && ctx->player.dir_y < 0)
		{
			ctx->player.pos_x = ctx->player.pos_x - step;
			if (check_new_pos(ctx))
				return (1);
			ctx->player.pos_x = ctx->player.pos_x + step;
			ctx->player.pos_y = ctx->player.pos_y - step;
			if (!check_new_pos(ctx))
				return (0);
		}
		else if (ctx->player.dir_x > 0 && ctx->player.dir_y < 0)
		{
			ctx->player.pos_x = ctx->player.pos_x + step;
			if (check_new_pos(ctx))
				return (1);
			ctx->player.pos_x = ctx->player.pos_x - step;
			ctx->player.pos_y = ctx->player.pos_y - step;
			if (!check_new_pos(ctx))
				return (0);
		}
		else if (ctx->player.dir_x > 0 && ctx->player.dir_y > 0)
		{
			ctx->player.pos_x = ctx->player.pos_x + step;
			if (check_new_pos(ctx))
				return (1);
			ctx->player.pos_x = ctx->player.pos_x - step;
			ctx->player.pos_y = ctx->player.pos_y + step;
			if (!check_new_pos(ctx))
				return (0);
		}
		else if (ctx->player.dir_x < 0 && ctx->player.dir_y > 0)
		{
			ctx->player.pos_x = ctx->player.pos_x - step;
			if (check_new_pos(ctx))
				return (1);
			ctx->player.pos_x = ctx->player.pos_x + step;
			ctx->player.pos_y = ctx->player.pos_y + step;
			if (!check_new_pos(ctx))
				return (0);
		}
		return (1);
	}
	return (1);
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
	{
		ctx->player.pos_x = ctx->player.pos_x + (ctx->player.dir_x * step);
		ctx->player.pos_y = ctx->player.pos_y + (ctx->player.dir_y * step);
	}
	if (ctx->keys.key_s == true)
	{
		ctx->player.pos_x = ctx->player.pos_x - (ctx->player.dir_x * step);
		ctx->player.pos_y = ctx->player.pos_y - (ctx->player.dir_y * step);
	}	
	if (ctx->keys.key_d == true)
	{
		ctx->player.pos_x = ctx->player.pos_x - (ctx->player.dir_y * step);
		ctx->player.pos_y = ctx->player.pos_y + (ctx->player.dir_x * step);
	}
	if (ctx->keys.key_a == true)
	{
		ctx->player.pos_x = ctx->player.pos_x + (ctx->player.dir_y * step);
		ctx->player.pos_y = ctx->player.pos_y - (ctx->player.dir_x * step);
	}
	if (!check_new_pos(ctx))
	{
		ctx->player.pos_x = old_pos_x;
		ctx->player.pos_y = old_pos_y;
		if (!(check_sliding_ag_walls(ctx, step)))
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
	{
		a = -0.05;
		tmp_x = ctx->player.dir_x * cos(a) + ctx->player.dir_y * (-sin(a));
		ctx->player.dir_y = ctx->player.dir_x * sin(a) + ctx->player.dir_y * (cos(a));
		ctx->player.dir_x = tmp_x;
		tmp_plane_x = ctx->ray.plane_x * cos(a) - ctx->ray.plane_y * sin(a);
		ctx->ray.plane_y =ctx->ray.plane_x * sin(a) + ctx->ray.plane_y * cos(a);
		ctx->ray.plane_x = tmp_plane_x;
	}
	else if (ctx->keys.key_right == true)
	{
		a = 0.05;
		tmp_x = ctx->player.dir_x * cos(a) + ctx->player.dir_y * (-sin(a));
		ctx->player.dir_y = ctx->player.dir_x * sin(a) + ctx->player.dir_y * (cos(a));
		ctx->player.dir_x = tmp_x;
		tmp_plane_x = ctx->ray.plane_x * cos(a) - ctx->ray.plane_y * sin(a);
		ctx->ray.plane_y =ctx->ray.plane_x * sin(a) + ctx->ray.plane_y * cos(a);
		ctx->ray.plane_x = tmp_plane_x;
	}
}