/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:03:44 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 15:04:07 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../utils_bonus.h"
#include "../init_bonus.h"
#include "../structs_bonus.h"
#include "../parse/parse_bonus.h"
#include "walls_bonus.h"

void	calc_draw_start_end(t_ctx *ctx)
{
	ctx->sprites.draw_start_y = -ctx->sprites.height / 2 + HEIGHT / 2;
	if (ctx->sprites.draw_start_y < 0)
		ctx->sprites.draw_start_y = 0;
	ctx->sprites.draw_end_y = ctx->sprites.height / 2 + HEIGHT / 2;
	if (ctx->sprites.draw_end_y >= HEIGHT)
		ctx->sprites.draw_end_y = HEIGHT - 1;
	ctx->sprites.width = abs((int)(HEIGHT / (ctx->sprites.trans_y)));
	ctx->sprites.draw_start_x = -ctx->sprites.width / 2 + ctx->sprites.screen_x;
	if (ctx->sprites.draw_start_x < 0)
		ctx->sprites.draw_start_x = 0;
	ctx->sprites.draw_end_x = ctx->sprites.width / 2 + ctx->sprites.screen_x;
	if (ctx->sprites.draw_end_x >= WIDTH)
		ctx->sprites.draw_end_x = WIDTH - 1;
}

void	draw_stripes(t_ctx *ctx, int stripe)
{
	int				y;
	unsigned int	color;
	int				d;
	int				tex_y;

	y = ctx->sprites.draw_start_y;
	while (++y < ctx->sprites.draw_end_y)
	{
		d = y * 256 - HEIGHT * 128 + ctx->sprites.height * 128;
		tex_y = ((d * ctx->texture.sprites[ctx->sprites.selec_tex].tex_height)
				/ ctx->sprites.height) / 256;
		color = (*(int *)(ctx->texture.sprites[ctx->sprites.selec_tex].addr + (4
						* ctx->texture.sprites[ctx->sprites.selec_tex].tex_width
						* (int)tex_y) + (4 * (int)ctx->sprites.tex_x)));
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&ctx->img_sprite, stripe, y, color);
	}
}

void	select_sprite_stage(t_ctx *ctx)
{
	int	cur_time;
	int	v;

	v = 1000000;
	cur_time = get_cur_time(ctx);
	if (cur_time % v >= 0 && cur_time % v <= v / 8)
		ctx->sprites.selec_tex = 0;
	else if (cur_time % v > v / 8 && cur_time % v <= v / 4)
		ctx->sprites.selec_tex = 1;
	else if (cur_time % v > v / 4 && cur_time % v <= (3 * v / 8))
		ctx->sprites.selec_tex = 2;
	else if (cur_time % v > 3 * v / 8 && cur_time % v <= v / 2)
		ctx->sprites.selec_tex = 3;
	else if (cur_time % v >= v / 2 && cur_time % v <= 5 * v / 8)
		ctx->sprites.selec_tex = 4;
	else if (cur_time % v > 5 * v / 8 && cur_time % v <= 3 * v / 4)
		ctx->sprites.selec_tex = 1;
	else if (cur_time % v > 3 * v / 4 && cur_time % v <= (7 * v / 8))
		ctx->sprites.selec_tex = 2;
	else
		ctx->sprites.selec_tex = 3;
}

void	draw_sprite(t_ctx *ctx)
{
	int	i;
	int	stripe;

	calc_order_sprite_dist(ctx);
	sort_sprites(ctx);
	i = -1;
	select_sprite_stage(ctx);
	while (++i < ctx->sprites.num)
	{
		transform_sprite_coord(ctx, i);
		calc_draw_start_end(ctx);
		stripe = ctx->sprites.draw_start_x;
		while (++stripe < ctx->sprites.draw_end_x)
		{
			ctx->sprites.tex_x = (int)(256 * (stripe - (-ctx->sprites.width / 2
							+ ctx->sprites.screen_x))
					* ctx->texture.sprites[ctx->sprites.selec_tex].tex_width
					/ ctx->sprites.width) / 256;
			if (ctx->sprites.trans_y > 0 && stripe > 0 && stripe < WIDTH
				&& ctx->sprites.trans_y < ctx->sprites.z_buffer[stripe])
				draw_stripes(ctx, stripe);
		}
	}
}
