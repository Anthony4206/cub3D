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

void	calc_height_wall(t_ctx *ctx)
{
	ctx->wall.line_height = (int)(HEIGHT / ctx->ray.perp_wall_dist);
	ctx->wall.draw_start = -ctx->wall.line_height / 2 + HEIGHT / 2;
	if (ctx->wall.draw_start < 0)
		ctx->wall.draw_start = 0;
	ctx->wall.draw_end = ctx->wall.line_height / 2 + HEIGHT / 2;
	if (ctx->wall.draw_end >= HEIGHT)
		ctx->wall.draw_end = HEIGHT - 1;
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
	int		color;

	step = 1.0 * ctx->tex.tex_height / ctx->wall.line_height;
	tex_pos = (ctx->wall.draw_start - HEIGHT / 2 + ctx->wall.line_height / 2) * step;
    y = ctx->wall.draw_start - 1;
    while (++y < ctx->wall.draw_end)
    {
        ctx->tex.texY = (int)tex_pos & (ctx->tex.tex_height - 1);
        tex_pos += step;
       	if (ctx->ray.hit_side == 1 && ctx->ray.ray_dirY < 0) // NORD
			color = 0xfabc3c; //yellow
			// color = ctx->tex.texture[0][ctx->tex.tex_height * ctx->tex.texY + ctx->tex.texX];
		else if (ctx->ray.hit_side == 0 && ctx->ray.ray_dirX > 0) // EST
			color = 0xFF0000;
			// color = ctx->tex.texture[1][ctx->tex.tex_height * ctx->tex.texY + ctx->tex.texX];
		else if (ctx->ray.hit_side == 1 && ctx->ray.ray_dirY > 0) // SUD
			color = 0x7dff42; //green
			// color = ctx->tex.texture[2][ctx->tex.tex_height * ctx->tex.texY + ctx->tex.texX];
		else if (ctx->ray.hit_side == 0 && ctx->ray.ray_dirX < 0) // OUEST
			color = 0xc442ff; //purple
			// color = ctx->tex.texture[3][ctx->tex.tex_height * ctx->tex.texY + ctx->tex.texX];
		ctx->screen.buffer[y][x] = color;
//		printf("BUFFER COLORED[%d][%d] = %d\n", y, x, ctx->screen.buffer[y][x]);
    }
}

/* Determines how much to increase the texture coordinate
// per screen pixel on the vertical stripe*/
// void	color_x_stripe(t_ctx *ctx, int x)
// {
//     double	step;
// 	double	tex_pos;
// 	int		y;
// 	int		color;

// 	step = 1.0 * ctx->tex.tex_height / ctx->wall.line_height;
// 	tex_pos = (ctx->wall.draw_start - HEIGHT / 2 + ctx->wall.line_height / 2) * step;
//     y = ctx->wall.draw_start;
//     while (++y < ctx->wall.draw_end)
//     {
//         ctx->tex.texY = (int)tex_pos & (ctx->tex.tex_height - 1);
//         tex_pos += step;
//        	if (ctx->ray.hit_side == 1 && ctx->ray.ray_dirY < 0) // NORD
// 			color = ctx->tex.texture[0][ctx->texture.N_wall.tex_height * ctx->tex.texY + ctx->tex.texX];
// 		else if (ctx->ray.hit_side == 0 && ctx->ray.ray_dirX > 0) // EST
// 			color = ctx->tex.texture[1][ctx->texture.E_wall.tex_height * ctx->tex.texY + ctx->tex.texX];
// 		else if (ctx->ray.hit_side == 1 && ctx->ray.ray_dirY > 0) // SUD
// 			color = ctx->tex.texture[2][ctx->texture.S_wall.tex_height * ctx->tex.texY + ctx->tex.texX];
// 		else if (ctx->ray.hit_side == 0 && ctx->ray.ray_dirX < 0) // OUEST
// 			color = ctx->tex.texture[3][ctx->texture.W_wall.tex_height * ctx->tex.texY + ctx->tex.texX];
//         if (ctx->ray.hit_side == 1) // pour assombrir... pas demandé
//             color = (color >> 1) & 8355711;
//         ctx->screen.buffer[y][x] = color;
//     }
// }

void	display_buffer(t_ctx *ctx)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
				printf("%d ", ctx->screen.buffer[y][x]);
		printf("\n");
	}
}

// void	display2_buffer(t_ctx *ctx)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y < WIDTH)
// 	{
// 		x = -1;
// 		while (++x < HEIGHT)
// 				printf("%d ", ctx->screen.buffer[y][x]);
// 		printf("\n");
// 	}
// }

// void	rotate_buffer(t_ctx *ctx)
// {
// 	int	x;
// 	int	y;
// 	unsigned int **buf;
// 	int x2;
// 	int	y2;

// 	printf("-----------BUFFER ROTATE---------\n");
// 	y = HEIGHT;
// 	x2 = 0;
// 	int	i = -1;
// 	buf = ft_calloc(sizeof(unsigned int *), WIDTH);
// 	while (++i < WIDTH)
// 		buf[i] = ft_calloc(sizeof(unsigned int), HEIGHT);
// 	while (--y > 0)
// 	{
// 		x = -1;
// 		y2 = 0;
// 		while (++x < WIDTH)
// 		{
// 			buf[y2][x2] = ctx->screen.buffer[y][x];
// 			y2++;
// 		}
// 		free(ctx->screen.buffer[y]);
// 		x2++;
// 	}
// 	free(ctx->screen.buffer);
// 	ctx->screen.buffer = buf;
// }

void	rotate_buffer(t_ctx *ctx)
{
	int	x;
	int	y;
	unsigned int **buf;
	int x2;
	int	y2;

	y = -1;
	x2 = 0;
	int	i = -1;
	buf = ft_calloc(sizeof(unsigned int *), WIDTH);
	while (++i < WIDTH)
		buf[i] = ft_calloc(sizeof(unsigned int), HEIGHT);
	while (++y < HEIGHT)
	{
		x = WIDTH;
		y2 = 0;
		while (--x > 0)
		{
			buf[y2][x2] = ctx->screen.buffer[y][x];
			y2++;
		}
		free(ctx->screen.buffer[y]);
		x2++;
	}
	free(ctx->screen.buffer);
	ctx->screen.buffer = buf;
}
void	draw_buffer(t_ctx *ctx)
{
	int	x;
	int	y;
	// int	y_bis;

	x = -1;
	display_buffer(ctx);
	//rotate_buffer(ctx);
	while (++x < WIDTH)
	{
		y = -1;
		// y_bis = HEIGHT - 1;
		while (++y < HEIGHT)
		{
			my_mlx_pixel_put(&ctx->img, y, x, ctx->screen.buffer[y][x]);
			// y_bis--;
		}
	}
}

void	clear_buffer(unsigned int **buffer)
{
	(void)buffer;
}

void    draw_wall(t_ctx *ctx, int x)
{
	calc_height_wall(ctx);
	ctx->tex.tex_num = ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] - '0' - 1;
	calc_wall_x(ctx);
	calc_x_coord_tex(ctx);
	color_x_stripe(ctx, x);
}
