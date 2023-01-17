/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:14:45 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/16 07:25:06 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../structs_bonus.h"
#include "walls_bonus.h"
#include "../init_bonus.h"

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
	player_moves(ctx);
	player_rotates(ctx);
	print_background(ctx);
	raycasting_walls(ctx);
	draw_and_clear_buffer(ctx);
	mlx_put_image_to_window(&ctx->mlx, ctx->win, ctx->img.img, 0, 0);
	draw_minimap(ctx);
    return (0);
}

int	take_instructions_and_draw(t_ctx *ctx)
{
	ft_bzero(ctx->img.addr, WIDTH * HEIGHT * 4);
	draw(ctx);
	mlx_hook(ctx->win, 2, 0, press_key, ctx);
	mlx_hook(ctx->win, 3, 0, release_key, ctx);
	mlx_hook(ctx->win, 17, 0, ft_close, ctx);
	mlx_hook(ctx->win, 4, 0, press_mouse, ctx);
	mlx_hook(ctx->win, 5, 0, release_mouse, ctx);
	mlx_hook(ctx->win, 6, 0, move_mouse, ctx);
    mlx_loop_hook(ctx->mlx, draw, ctx);
	mlx_loop(ctx->mlx);
	return (0);
}
