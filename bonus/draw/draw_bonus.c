/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:14:45 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 07:20:47 by alevasse         ###   ########.fr       */
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
			ctx->screen.buffer[y][x] = ctx->parse.c_rgb;
	}
	y--;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ctx->screen.buffer[y][x] = ctx->parse.f_rgb;
	}
}

void	print_transparent_background(t_data *img)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(img, x, y, 0xFFFFFFFF);
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

//camera_x: points to the right vertical stripe, x-coordinate on the camera plane
//with camera_x=0 being the center, camX=-1 being left side, camX=1 being right side
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
	print_transparent_background(&ctx->img_door);
    raycasting_doors(ctx);
	print_transparent_background(&ctx->img_sprite);
	draw_sprite(ctx);
	draw_and_clear_buffer(ctx);
	mlx_put_image_to_window(&ctx->mlx, ctx->win, ctx->img.img, 0, 0);
	mlx_put_image_to_window(&ctx->mlx, ctx->win, ctx->img_door.img, 0, 0);
	mlx_put_image_to_window(&ctx->mlx, ctx->win, ctx->img_sprite.img, 0, 0);
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
