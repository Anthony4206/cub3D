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
#include "draw.h"

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

/*CameraX: points to the right vertical stripe
(x-coord on the camera plane), with camera_x=0 being the center,
camX=-1 being left side, camX=1 being right side.
*/
int	draw(t_ctx *ctx)
{
	ft_bzero(ctx->img.addr, WIDTH * HEIGHT * 4);
	player_moves(ctx);
	player_rotates(ctx);
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
	mlx_hook(ctx->win, 2, 0, press_key, ctx);
	mlx_hook(ctx->win, 3, 0, release_key, ctx);
	mlx_loop_hook(ctx->mlx, draw, ctx);
	mlx_loop(ctx->mlx);
	return (0);
}
