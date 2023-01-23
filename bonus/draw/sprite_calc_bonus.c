/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:04:11 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 15:04:13 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../utils_bonus.h"
#include "../init_bonus.h"
#include "../structs_bonus.h"
#include "../parse/parse_bonus.h"
#include "draw_bonus.h"

int	sprites_are_sorted(t_sprites sprites)
{
	int	i;

	i = -1;
	while (++i < sprites.num - 1)
	{
		if (sprites.sprite_distance[sprites.order[i]]
			< sprites.sprite_distance[sprites.order[i + 1]])
			return (0);
	}
	return (1);
}

//Sorts sprites from the furthest to the closest
void	sort_sprites(t_ctx *ctx)
{
	int	i;
	int	tmp;

	while (!sprites_are_sorted(ctx->sprites))
	{
		i = -1;
		while (++i < ctx->sprites.num - 1)
		{
			if (ctx->sprites.sprite_distance[ctx->sprites.order[i]]
				< ctx->sprites.sprite_distance[ctx->sprites.order[i + 1]])
			{
				tmp = ctx->sprites.order[i];
				ctx->sprites.order[i] = ctx->sprites.order[i + 1];
				ctx->sprites.order[i + 1] = tmp;
			}
		}
	}
}

void	calc_order_sprite_dist(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->sprites.num)
	{
		ctx->sprites.order[i] = i;
		ctx->sprites.sprite_distance[i] = ((ctx->player.pos_x
					- ctx->sprites.sprite[i].x)
				* (ctx->player.pos_x - ctx->sprites.sprite[i].x)
				+ (ctx->player.pos_y - ctx->sprites.sprite[i].y)
				* (ctx->player.pos_y - ctx->sprites.sprite[i].y));
	}
}

//trans_y is actually the depth inside the screen, that what Z is in 3D
//using 'trans_y' instead of the real distance prevents fisheye
void	transform_sprite_coord(t_ctx *ctx, int i)
{
	double	inv_det;

	ctx->sprites.sprite_x = ctx->sprites.sprite[ctx->sprites.order[i]].x
		- ctx->player.pos_x;
	ctx->sprites.sprite_y = ctx->sprites.sprite[ctx->sprites.order[i]].y
		- ctx->player.pos_y;
	inv_det = 1.0 / (ctx->ray.plane_x * ctx->player.dir_y
			- ctx->player.dir_x * ctx->ray.plane_y);
	ctx->sprites.trans_x = inv_det * (ctx->player.dir_y * ctx->sprites.sprite_x
			- ctx->player.dir_x * ctx->sprites.sprite_y);
	ctx->sprites.trans_y = inv_det * (-ctx->ray.plane_y * ctx->sprites.sprite_x
			+ ctx->ray.plane_x * ctx->sprites.sprite_y);
	ctx->sprites.screen_x = (int)((WIDTH / 2) * (1 + ctx->sprites.trans_x
				/ ctx->sprites.trans_y));
	ctx->sprites.height = abs((int)(HEIGHT / ctx->sprites.trans_y));
}
