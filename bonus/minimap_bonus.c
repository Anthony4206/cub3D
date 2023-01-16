/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 06:48:58 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/16 10:25:40 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "structs_bonus.h"
#include "draw/walls_bonus.h"

void    init_mini_map(t_ctx *ctx)
{
	ctx->mini.mini_map.img = mlx_new_image(ctx->mlx, M_WIDTH, M_HEIGHT);
	ctx->mini.mini_map.addr = mlx_get_data_addr(ctx->mini.mini_map.img,
		&ctx->mini.mini_map.bpp, &ctx->mini.mini_map.line_len,
			&ctx->mini.mini_map.endian);
}

void	print_background_minimap(t_ctx *ctx)
{
	int x;
	int y;

	y = -1;
	while (++y < M_HEIGHT)
	{
		x = -1;
		while (++x < M_WIDTH)
			my_mlx_pixel_put(&ctx->mini.mini_map, x, y, 0x70FFB266);
	}
}

void	print_wall(t_ctx *ctx, int i, int j)
{
	int	size_max;

	size_max = SIZE_MAX / 2;
	if (ctx->player.posX - size)
}

void	draw_walls_mini_map(t_ctx *ctx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < ctx->parse.map_height)
	{
		j = -1;
		while (++j < ctx->parse.map_width)
		{
			if (ctx->parse.map[i][j] == '1')
				print_wall(ctx, i * SIZE_MAX, j * SIZE_MAX);
		}
	}
}

void    draw_minimap(t_ctx *ctx)
{
	ft_bzero(ctx->mini.mini_map.addr, (M_WIDTH) * (M_HEIGHT) * 4);
	print_background_minimap(ctx);
	draw_walls_mini_map(ctx);
	mlx_put_image_to_window(&ctx->mlx, ctx->win, ctx->mini.mini_map.img, 0, 0);

    // Attribuer des couleurs en fonction des valeurs de char **map
    // 1 pixel devient 10 pixels
    // faire bouger le perso dans la minimap avec les keys
    // vérifier qu'on se déplace sur un 0
    // pour déssiner la map on procède comme pour déssiner cub3D
}
