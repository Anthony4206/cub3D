/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sliding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:44:21 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/20 15:44:23 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../structs_bonus.h"
#include "walls_bonus.h"

int	get_texture(t_ctx *ctx, int x, int y)
{
	if (ctx->parse.map[(int)y][(int)x] == '1'
		|| ctx->parse.map[(int)y][(int)x] == 'D'
		|| ctx->parse.map[(int)y][(int)x] == 'A')
		return (1);
	return (0);
}

int	check_sliding_pos_x(t_ctx *ctx, float step, int sign)
{
	ctx->player.pos_x = ctx->player.pos_x + (sign * step);
	if (check_new_pos(ctx))
		return (1);
	return (0);
}

int	check_sliding_pos_y(t_ctx *ctx, float step, int sign)
{
	ctx->player.pos_y = ctx->player.pos_y + (sign * step);
	if (check_new_pos(ctx))
		return (1);
	return (0);
}

int	check_sliding_bis(t_ctx *ctx, float step)
{
	if (ctx->player.dir_x > 0 && ctx->player.dir_y > 0)
	{
		if (check_sliding_pos_x(ctx, step, 1))
			return (1);
		ctx->player.pos_x = ctx->player.pos_x - step;
		if (!check_sliding_pos_y(ctx, step, 1))
			return (0);
	}
	else if (ctx->player.dir_x < 0 && ctx->player.dir_y > 0)
	{
		if (check_sliding_pos_x(ctx, step, -1))
			return (1);
		ctx->player.pos_x = ctx->player.pos_x + step;
		if (!check_sliding_pos_y(ctx, step, 1))
			return (0);
	}
	return (1);
}

int	sliding_ag_walls(t_ctx *ctx, float step)
{
	if (ctx->keys.key_w == true)
	{
		if (ctx->player.dir_x == 0 || ctx->player.dir_y == 0)
			return (0);
		if (ctx->player.dir_x < 0 && ctx->player.dir_y < 0)
		{
			if (check_sliding_pos_x(ctx, step, -1))
				return (1);
			ctx->player.pos_x = ctx->player.pos_x + step;
			if (!check_sliding_pos_y(ctx, step, -1))
				return (0);
		}
		else if (ctx->player.dir_x > 0 && ctx->player.dir_y < 0)
		{
			if (check_sliding_pos_x(ctx, step, 1))
				return (1);
			ctx->player.pos_x = ctx->player.pos_x - step;
			if (!check_sliding_pos_y(ctx, step, -1))
				return (0);
		}
		if (!check_sliding_bis(ctx, step))
			return (0);
	}
	return (1);
}
