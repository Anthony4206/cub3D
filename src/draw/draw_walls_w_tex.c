/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:30:46 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/10 10:48:22 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../init.h"
#include "../structs.h"
#include "walls.h"
#include "../parse/parse.h"

void	get_texture(t_ctx *ctx)
{
	if (ctx->ray.hit_side == 1 )
	{
		if (ctx->ray.ray_dirY <= 0) 
		{
			if (ctx->player.dirX >= 0 ) // orient N et EST
				ctx->wall.texture = ctx->texture.N_wall; //mur nord
			else
				ctx->wall.texture = ctx->texture.S_wall;//orient ouest mur sud
		}
		else
		{
			if (ctx->player.dirX >= 0 ) // orient S et EST
				ctx->wall.texture = ctx->texture.S_wall;
			else
				ctx->wall.texture = ctx->texture.N_wall;
		}
	}
	else 
	{
		if (ctx->ray.ray_dirX <= 0) 
		{
			if (ctx->player.dirY <= 0) // orient N et OUEST
				ctx->wall.texture = ctx->texture.W_wall; //mur ouest
			else
				ctx->wall.texture = ctx->texture.E_wall; //orient sud mur est
		}
		else
		{
			if (ctx->player.dirY <= 0) // orient N et EST
				ctx->wall.texture = ctx->texture.E_wall; //mur est
			else
				ctx->wall.texture = ctx->texture.W_wall;//orient sud mur ouest
		}
	}
}

void    draw_wall(t_ctx *ctx, int x)
{
	//ctx->tex.tex_num = ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] - '0' - 1;
	get_texture(ctx);
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
	ctx->tex.texX = (int)(ctx->tex.wallX * (double)ctx->wall.texture.tex_width);
    if (ctx->ray.hit_side == 0 && ctx->ray.ray_dirX > 0)
        ctx->tex.texX = ctx->wall.texture.tex_width - ctx->tex.texX - 1;
    if (ctx->ray.hit_side == 1 && ctx->ray.ray_dirY < 0) 
        ctx->tex.texX = ctx->wall.texture.tex_width - ctx->tex.texX - 1;
}

/* Determines how much to increase the texture coordinate
per screen pixel on the vertical stripe*/
void	color_x_stripe(t_ctx *ctx, int x)
{
    double	step;
	double	tex_pos;
	int		y;
	int		color;

	step = 1.0 * ctx->wall.texture.tex_height / ctx->wall.line_height;
	tex_pos = (ctx->wall.draw_start - HEIGHT / 2 + ctx->wall.line_height / 2) * step;
    y = ctx->wall.draw_start - 1;
    while (++y < ctx->wall.draw_end)
    {
        ctx->tex.texY = (int)tex_pos & (ctx->wall.texture.tex_height - 1);
        tex_pos += step;
		color = (*(int*)(ctx->wall.texture.addr + (4 * ctx->wall.texture.tex_width * (int)ctx->tex.texY) + (4 * (int)ctx->tex.texX)));
		ctx->screen.buffer[y][x] = color;
    }
}

