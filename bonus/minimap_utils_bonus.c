/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:20:59 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 14:40:51 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "draw/walls_bonus.h"

void	print_background_wdt(t_ctx *ctx, int scale)
{
	int	x;
	int	y;
	int	size;

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

void	print_background_minimap(t_ctx *ctx, int scale)
{
	int	x;
	int	y;
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
		print_background_wdt(ctx, scale);
}
