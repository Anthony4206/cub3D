/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_w_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:30:46 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/13 12:35:24 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../init.h"
#include "../structs.h"
#include "../parse/parse.h"
#include "walls.h"

void    init_tex_dir(t_ctx *ctx)
{
    if (ctx->ray.hit_side == 1 && ctx->ray.ray_dirY < 0)
        ctx->tex.select_tex = ctx->texture.N_wall;
    else if (ctx->ray.hit_side == 1 && ctx->ray.ray_dirY >= 0)
        ctx->tex.select_tex = ctx->texture.S_wall;
    else if (ctx->ray.hit_side == 0 && ctx->ray.ray_dirX >= 0)
        ctx->tex.select_tex = ctx->texture.E_wall;
    else if (ctx->ray.hit_side == 0 && ctx->ray.ray_dirX < 0)
        ctx->tex.select_tex = ctx->texture.W_wall;
}

void    draw_wall(t_ctx *ctx, int x)
{
//	ctx->tex.tex_num = ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] - '0' - 1;
	init_tex_dir(ctx);
	calc_wall_x(ctx);
	calc_x_coord_tex(ctx);
	color_x_stripe(ctx, x);
}

void	calc_wall_x(t_ctx *ctx)
{
	if (ctx->ray.hit_side == 0)
        ctx->tex.wallX = ctx->player.posY + ctx->ray.perp_wall_dist * ctx->ray.ray_dirY;
    else
		ctx->tex.wallX = ctx->player.posX + ctx->ray.perp_wall_dist * ctx->ray.ray_dirX;
    ctx->tex.wallX -= floor((ctx->tex.wallX));
}

/* The x-coordinate of the texture will remain the same,
because we stay in the same vertical stripe of the screen.
->Now we need a loop in the y-direction to give each pixel of the vertical
stripe the correct y-coordinate of the texture, called texY.*/
void	calc_x_coord_tex(t_ctx *ctx)
{
	ctx->tex.texX = (int)(ctx->tex.wallX * (double)ctx->tex.tex_width);
    if (ctx->ray.hit_side == 0 && ctx->ray.ray_dirX > 0)
        ctx->tex.texX = ctx->tex.tex_width - ctx->tex.texX - 1;
    if (ctx->ray.hit_side == 1 && ctx->ray.ray_dirY < 0)
        ctx->tex.texX = ctx->tex.tex_width - ctx->tex.texX - 1;
}

/* Determines how much to increase the texture coordinate
per screen pixel on the vertical stripe*/
void	color_x_stripe(t_ctx *ctx, int x)
{
		double	step;
		double	tex_pos;
		int		y;
//		int		color;

		step = 1.0 * ctx->tex.select_tex.tex_height / ctx->wall.line_height;
		tex_pos = (ctx->wall.draw_start - HEIGHT / 2 +
			ctx->wall.line_height / 2) * step;
		y = ctx->wall.draw_start - 1;
		while (++y < ctx->wall.draw_end)
		{
			ctx->tex.texY = (int)tex_pos & (ctx->tex.select_tex.tex_height - 1);
//			printf("texpos : %d\n", )
			tex_pos += step;
	      	if (y < HEIGHT && x < WIDTH)
			{
//				printf("color : %x\n", ctx->tex.select_tex.addr[ctx->tex.texY *
//				ctx->tex.select_tex.line_len / 4 + ctx->tex.texX]);
				ctx->screen.buffer[y][x] = 
				create_rgb(ctx->tex.select_tex.addr[ctx->tex.texY *
				ctx->tex.select_tex.line_len / 4 + ctx->tex.texX],
				ctx->tex.select_tex.addr[ctx->tex.texY *
				ctx->tex.select_tex.line_len / 4 + ctx->tex.texX + 1],
				ctx->tex.select_tex.addr[ctx->tex.texY *
				ctx->tex.select_tex.line_len / 4 + ctx->tex.texX + 2]);
			}
/*		if (ctx->ray.hit_side == 1)
		{
			if (ctx->ray.ray_dirY <= 0) 
			{
					color = ctx->texture.N_wall.addr[ctx->texture.N_wall.tex_height * ctx->tex.texY + ctx->tex.texX]; //mur nord
			}
			else
			{
					color = ctx->texture.S_wall.addr[ctx->texture.S_wall.tex_height * ctx->tex.texY + ctx->tex.texX]; //mur sud
			}
		}
		else
		{
			if (ctx->ray.ray_dirX <= 0)
			{
					color = ctx->texture.W_wall.addr[ctx->texture.W_wall.tex_height * ctx->tex.texY + ctx->tex.texX]; //mur ouest
			}
			else
			{
					color = ctx->texture.E_wall.addr[ctx->texture.E_wall.tex_height * ctx->tex.texY + ctx->tex.texX]; //mur est
			}
		}
		ctx->screen.buffer[y][x] = color;*/
	}
}

