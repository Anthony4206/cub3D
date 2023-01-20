/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 06:48:58 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 10:03:56 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "structs_bonus.h"
#include "draw/walls_bonus.h"
#include "utils_bonus.h"

void    init_mini_map(t_ctx *ctx)
{
	ctx->mini.mini_map.img = mlx_new_image(ctx->mlx, M_WIDTH, M_HEIGHT);
	ctx->mini.mini_map.addr = mlx_get_data_addr(ctx->mini.mini_map.img,
		&ctx->mini.mini_map.bpp, &ctx->mini.mini_map.line_len,
			&ctx->mini.mini_map.endian);
}

void	print_background_minimap(t_ctx *ctx, int scale)
{
	int x;
	int y;
	int	size;

	if (ctx->parse.map_height > ctx->parse.map_width)
	{
		size = scale * (ctx->parse.map_width + 1);
		y = -1;
		while (++y < M_HEIGHT)
		{
			x = -1;
			while (++x < size)
				my_mlx_pixel_put(&ctx->mini.mini_map, x, y, 0x70FFB266);
			x--;
			while (++x < M_WIDTH)
				my_mlx_pixel_put(&ctx->mini.mini_map, x, y, 0xFFFFB266);
		}
	}
	else
	{
		size = scale * (ctx->parse.map_height + 3);
		y = -1;
		while (++y < size)
		{
			x = -1;
			while (++x < M_WIDTH)
				my_mlx_pixel_put(&ctx->mini.mini_map, x, y, 0x70FFB266);
		}
		y--;
		while (++y < M_HEIGHT)
		{
			x = -1;
			while (++x < M_WIDTH)
				my_mlx_pixel_put(&ctx->mini.mini_map, x, y, 0xFFFFB266);
		}
	}
}

void	print_wall(t_ctx *ctx, int scale, int x, int y)
{
	int	save_y;
	int	save_x;

	save_y = y;
	save_x = x;
	y--;
	while (++y < save_y + scale)
	{
		x = save_x - 1;
		while (++x < save_x + scale)
			my_mlx_pixel_put(&ctx->mini.mini_map, x, y, 0x70000000);
	}
}

void	draw_walls_mini_map(t_ctx *ctx, int scale)
{
	int	i;
	int	j;

	j = -1;
	while (++j < ctx->parse.map_height)
	{
		i = -1;
		while (++i < ctx->parse.map_width)
		{
			if (ctx->parse.map[j][i] == '1')
				print_wall(ctx, scale, (i * scale) + 5, (j * scale) + 5);
		}
	}
}

void    draw_player(t_ctx *ctx, int scale)
{
    int x;
    int y;
    int incr_x;
    int incr_y;

    x = ctx->player.posX * scale + (scale / 3);
    y = ctx->player.posY * scale + (scale / 3);
    incr_y = -1;
    while (++incr_y < (scale / 3) * 2)
    {
        incr_x = -1;
        while (++incr_x < (scale / 3) * 2)
            my_mlx_pixel_put(&ctx->mini.mini_map, x + incr_x,
                y + incr_y, 0x70FF0000);
    }
}

void    draw_minimap(t_ctx *ctx)
{
	int	scale;

	if (ctx->parse.map_height > 100 || ctx->parse.map_width > 100)
		error_exit("Error\nThis map size is not available \
in beta, wait for patch 1.0.25\n");
	if (ctx->parse.map_height > ctx->parse.map_width)
		scale = M_HEIGHT / ctx->parse.map_height;
	else
		scale = M_WIDTH / ctx->parse.map_width;	
	ft_bzero(ctx->mini.mini_map.addr, (M_WIDTH) * (M_HEIGHT) * 4);
	print_background_minimap(ctx, scale);
	draw_walls_mini_map(ctx, scale);
    draw_player(ctx, scale);
	mlx_put_image_to_window(&ctx->mlx, ctx->win, ctx->mini.mini_map.img, 0, 0);
}
