/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:14:45 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/10 09:37:26 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../structs.h"
#include "walls.h"

void	print_background(t_ctx *ctx)
{
	int	y;
	int	x;

	y = -1;
	while (++y < (HEIGHT / 2))
	{
		x = -1;
		while (++x < WIDTH)
			ctx->screen.buffer[y][x] = ctx->parse.C_RGB;
	}
	y--;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ctx->screen.buffer[y][x] = ctx->parse.F_RGB;
	}
}

void	draw_and_clear_buffer(t_ctx *ctx)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(&ctx->img, x, y, ctx->screen.buffer[y][x]);
	}
	y = -1;
	while (++y < HEIGHT)
		ft_bzero(ctx->screen.buffer[y], WIDTH);
}

//cameraX: points to the right vertical stripe, x-coordinate on the camera plane
//with cameraX=0 being the center, camX=-1 being left side, camX=1 being right side
//x is the x-coord on the screen (ex:50 is at the center of a 100-wide screen)
//w is the width of the screen
//PAS A INITIALISER: CALCULATION for each ray dir_vector coordinates
int	draw(t_ctx *ctx)
{
	ft_bzero(ctx->img.addr, WIDTH * HEIGHT * 4);
	print_background(ctx);
	raycasting_walls(ctx);
	draw_and_clear_buffer(ctx);
	mlx_put_image_to_window(&ctx->mlx, ctx->win, ctx->img.img, 0, 0);
    return (0);
}

int	take_instructions_and_draw(t_ctx *ctx)
{
	ft_bzero(ctx->img.addr, WIDTH * HEIGHT * 4);
	draw(ctx);
	mlx_hook(ctx->win, 2, 0, deal_key, ctx);
    mlx_loop_hook(ctx->mlx, draw, ctx);
	// mlx_hook(global->win_id, 17, 0, close_window_mouse, global);
	// mlx_hook(global->win_id, 4, 0, press_mouse, global);
	// mlx_hook(global->win_id, 5, 0,release_mouse, global);
	// mlx_hook(global->win_id, 6, 0, move_mouse, global); 
	mlx_loop(ctx->mlx);
	return (0);
}
