/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_doors_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:43:50 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/23 10:48:07 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs_bonus.h"
#include "draw_bonus.h"

void	color_x_stripe_door(t_ctx *ctx, int x)
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
		color = (*(int *)(ctx->tex.select_tex.addr + (4
						* ctx->tex.select_tex.tex_width * (int)ctx->tex.tex_y)
					+ (4 * (int)ctx->tex.tex_x)));
		my_mlx_pixel_put(&ctx->img_door, x, y, color);
	}
	if (ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == '1' ||
		ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == 'D' ||
		(ctx->parse.map[ctx->ray.map_y][ctx->ray.map_x] == 'O' &&
		color == 0x261B1B))
		ctx->sprites.z_buffer[x] = ctx->ray.perp_wall_dist;
}

int	pos_door(char **map, int x, int y)
{
	if (map[y + 1][x] == 'D' || map[y - 1][x] == 'D' || map[y][x + 1] == 'D' ||
		map[y][x - 1] == 'D' || map[y + 1][x] == 'O' || map[y - 1][x] == 'O' ||
		map[y][x + 1] == 'O' || map[y][x - 1] == 'O')
	{
		if (map[y + 1][x] == 'D')
			map[y + 1][x] = 'O';
		else if (map[y + 1][x] == 'O')
			map[y + 1][x] = 'D';
		if (map[y - 1][x] == 'D')
			map[y - 1][x] = 'O';
		else if (map[y - 1][x] == 'O')
			map[y - 1][x] = 'D';
		if (map[y][x + 1] == 'D')
			map[y][x + 1] = 'O';
		else if (map[y][x + 1] == 'O')
			map[y][x + 1] = 'D';
		if (map[y][x - 1] == 'D')
			map[y][x - 1] = 'O';
		else if (map[y][x - 1] == 'O')
			map[y][x - 1] = 'D';
		return (1);
	}
	return (0);
}

void	init_tex_door(t_ctx *ctx)
{
	if (ctx->parse.map_door[ctx->ray.map_y][ctx->ray.map_x])
	{
		ctx->tex.select_tex = ctx->texture.tex_door[4];
		if (ctx->keys.key_door
			&& pos_door(ctx->parse.map, ctx->player.pos_x, ctx->player.pos_y))
			ctx->keys.key_door = false;
	}
	else
	{
		ctx->tex.select_tex = ctx->texture.tex_door[0];
		if (ctx->keys.key_door
			&& pos_door(ctx->parse.map, ctx->player.pos_x, ctx->player.pos_y))
			ctx->keys.key_door = false;
	}
}

void	draw_door(t_ctx *ctx, int x)
{
	init_tex_door(ctx);
	calc_wall_x(ctx);
	calc_x_coord_tex(ctx);
	color_x_stripe_door(ctx, x);
}
