/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_w_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:30:46 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/16 13:03:39 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../init.h"
#include "../structs.h"
#include "../parse/parse.h"
#include "draw.h"
#include "../parse/parse.h"

void	init_tex_dir(t_ctx *ctx)
{
	if (ctx->ray.hit_side == 1 && ctx->ray.ray_dir_y < 0)
		ctx->tex.select_tex = ctx->texture.n_wall;
	else if (ctx->ray.hit_side == 1 && ctx->ray.ray_dir_y >= 0)
		ctx->tex.select_tex = ctx->texture.s_wall;
	else if (ctx->ray.hit_side == 0 && ctx->ray.ray_dir_x >= 0)
		ctx->tex.select_tex = ctx->texture.e_wall;
	else if (ctx->ray.hit_side == 0 && ctx->ray.ray_dir_x < 0)
		ctx->tex.select_tex = ctx->texture.w_wall;
}

void	draw_wall(t_ctx *ctx, int x)
{
	init_tex_dir(ctx);
	init_tex_dir(ctx);
	calc_wall_x(ctx);
	calc_x_coord_tex(ctx);
	color_x_stripe(ctx, x);
}

void	calc_wall_x(t_ctx *ctx)
{
	if (ctx->ray.hit_side == 0)
		ctx->tex.wall_x = ctx->player.pos_y
			+ ctx->ray.perp_wall_dist * ctx->ray.ray_dir_y;
	else
		ctx->tex.wall_x = ctx->player.pos_x
			+ ctx->ray.perp_wall_dist * ctx->ray.ray_dir_x;
	ctx->tex.wall_x -= floor((ctx->tex.wall_x));
}

/* The x-coordinate of the texture will remain the same,
because we stay in the same vertical stripe of the screen.
->Loop in the y-direction to give each pixel of the vertical stripe
the correct y-coordinate of the texture, called tex_y.*/
void	calc_x_coord_tex(t_ctx *ctx)
{
	ctx->tex.tex_x = (int)(ctx->tex.wall_x
			* (double)ctx->tex.select_tex.tex_width);
	if (ctx->ray.hit_side == 0 && ctx->ray.ray_dir_x > 0)
		ctx->tex.tex_x = ctx->tex.select_tex.tex_width - ctx->tex.tex_x - 1;
	if (ctx->ray.hit_side == 1 && ctx->ray.ray_dir_y < 0)
		ctx->tex.tex_x = ctx->tex.select_tex.tex_width - ctx->tex.tex_x - 1;
}

/* Determines how much to increase the texture coordinate
per screen pixel on the vertical stripe*/
void	color_x_stripe(t_ctx *ctx, int x)
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
		color = (*(int *)(ctx->tex.select_tex.addr
					+ (4 * ctx->tex.select_tex.tex_width * (int)ctx->tex.tex_y)
					+ (4 * (int)ctx->tex.tex_x)));
		ctx->screen.buffer[y][x] = color;
	}
}
