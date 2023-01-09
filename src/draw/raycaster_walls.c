/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:21:24 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/09 10:01:30 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../utils.h"
#include "../init.h"
#include "../structs.h"
#include "../parse/parse.h"
#include "walls.h"
#include <stdio.h>

//A CHANGER AVEC LES TEXTURES IMPORTEES
void	generate_texture(t_ctx *ctx)
{
	printf("ctx->tex.tex_width = %d\n", ctx->tex.tex_width);
	printf("ctx->tex.tex_height = %d\n", ctx->tex.tex_height);
	ctx->tex.texture = ft_calloc(4, sizeof(int *));
	ctx->tex.texture[0] = ft_calloc(ctx->tex.tex_width * ctx->tex.tex_height + ctx->tex.tex_width, sizeof(int));
	ctx->tex.texture[1] = ft_calloc(ctx->tex.tex_width * ctx->tex.tex_height + ctx->tex.tex_width, sizeof(int));
	ctx->tex.texture[2] = ft_calloc(ctx->tex.tex_width * ctx->tex.tex_height + ctx->tex.tex_width, sizeof(int));
	ctx->tex.texture[3] = ft_calloc(ctx->tex.tex_width * ctx->tex.tex_height + ctx->tex.tex_width, sizeof(int));
	printf("taille CALLOC TEXTURE = %d\n", ctx->tex.tex_width * ctx->tex.tex_height + ctx->tex.tex_width);
	for(int x = 0; x < ctx->tex.tex_width; x++)
	for(int y = 0; y < ctx->tex.tex_height; y++)
{
	int xorcolor = (x * 256 / ctx->tex.tex_width) ^ (y * 256 / ctx->tex.tex_height);
	//int xcolor = x * 256 / texWidth;
	//int ycolor = y * 256 / ctx->tex.tex_height;
	int xycolor = y * 128 / ctx->tex.tex_height + x * 128 / ctx->tex.tex_width;
	ctx->tex.texture[0][ctx->tex.tex_width * y + x] = 65536 * 254 * (x != y && x != ctx->tex.tex_width - y); //flat red texture with black cross
	ctx->tex.texture[1][ctx->tex.tex_width * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
	ctx->tex.texture[2][ctx->tex.tex_width * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
	ctx->tex.texture[3][ctx->tex.tex_width * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
}
}

void	init_screen_buffer(t_ctx *ctx)
{
	int	i = -1;

	ctx->screen.buffer = malloc(sizeof(unsigned int *) * HEIGHT);
	while (++i < HEIGHT)
		ctx->screen.buffer[i] = malloc(sizeof(unsigned int) * WIDTH);
}

//cameraX: points to the right vertical stripe, x-coordinate on the camera plane
//with cameraX=0 being the center, camX=-1 being left side, camX=1 being right side
//x is the x-coord on the screen (ex:50 is at the center of a 100-wide screen)
//w is the width of the screen
//PAS A INITIALISER: CALCULATION for each ray dir_vector coordinates
void	raycasting_walls(t_ctx *ctx)
{
	int	x;
	
	x = 0;
	ctx->tex.tex_width = 64;
	ctx->tex.tex_height = 64;
	generate_texture(ctx);
	ctx->ray.mapX = (int)ctx->player.posX;
	printf("INIT map X = %d\n", ctx->ray.mapX);
	printf("INIT map Y = %d\n", ctx->ray.mapY);
	ctx->ray.mapY = (int)ctx->player.posY;
	init_screen_buffer(ctx);
	while (x++ < WIDTH)
	{
		ctx->ray.cameraX = 2 * x / (double)WIDTH - 1;
		ctx->ray.ray_dirX = ctx->player.dirX + ctx->ray.plane_X * ctx->ray.cameraX;
		ctx->ray.ray_dirY = ctx->player.dirY + ctx->ray.plane_Y * ctx->ray.cameraX;
		if (ctx->ray.ray_dirX == 0)
			ctx->ray.delta_distX = 1e30;
		else
			ctx->ray.delta_distX = fabs(1 / ctx->ray.ray_dirX);
		if (ctx->ray.ray_dirY == 0)
			ctx->ray.delta_distY = 1e30;
		else
			ctx->ray.delta_distY = fabs(1 / ctx->ray.ray_dirY);
		calculate_side_dist(ctx);
		printf("DEPART X = %d\n", x);
		exec_dda(ctx);
		calc_perp_wall_dist(ctx);
		draw_wall(ctx, x);
	}
}

//stepX and StepY eather -1 or +1 to indicate the dir of the ray
void	calculate_side_dist(t_ctx *ctx)
{
	if (ctx->ray.ray_dirX < 0)
	{
		ctx->ray.stepX = -1;
		ctx->ray.side_distX = (ctx->player.posX - ctx->ray.mapX) * ctx->ray.delta_distX;
	}
	else
	{
		ctx->ray.stepX = 1;
		ctx->ray.side_distX = (ctx->ray.mapX + 1.0 - ctx->player.posX) * ctx->ray.delta_distX;
	}
	if (ctx->ray.ray_dirY < 0)
	{
		ctx->ray.stepY = -1;
		ctx->ray.side_distY = (ctx->player.posY - ctx->ray.mapY) * ctx->ray.delta_distY;	
	}
	else
	{
		ctx->ray.stepY = 1;
		ctx->ray.side_distY = (ctx->ray.mapY + 1.0 - ctx->player.posY) * ctx->ray.delta_distY;
	}
}
//if side == 1, we bumped a Yline => N or S wall
// if side == 0, a x-line => E or W wall
//we check if the square we bumped into belongs to a wall, if yes, we stop
void	exec_dda(t_ctx *ctx)
{
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (ctx->ray.side_distX < ctx->ray.side_distY)
		{
			ctx->ray.side_distX += ctx->ray.delta_distX;
			ctx->ray.mapX += ctx->ray.stepX;
			ctx->ray.hit_side = 0;
		}
		else
		{
			ctx->ray.side_distY += ctx->ray.delta_distY;
			ctx->ray.mapY += ctx->ray.stepY;
			ctx->ray.hit_side = 1;			
		}
		printf("----- TEEEEST ctx->parse.map[%d][%d]", ctx->ray.mapY, ctx->ray.mapX);
		fflush(stdout);
		printf("= %d\n", ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] - '0');
		fflush(stdout);
		if (ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] - '0' > 0)
			hit = true;
	}
}

void	calc_perp_wall_dist(t_ctx *ctx)
{
	if (ctx->ray.hit_side == 0)
		ctx->ray.perp_wall_dist = (ctx->ray.side_distX - ctx->ray.delta_distX);
	else
		ctx->ray.perp_wall_dist = (ctx->ray.side_distY - ctx->ray.delta_distY);
}
