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

#include <mlx.h>
#include <libft.h>

#include "../structs.h"
#include "walls.h"

void	print_background(t_ctx *ctx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (HEIGHT / 2))
	{
		j = -1;
		while (++j < WIDTH)
			my_mlx_pixel_put(&ctx->img, j, i, ctx->parse.C_RGB);
	}
	i--;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			my_mlx_pixel_put(&ctx->img, j, i, ctx->parse.F_RGB);
	}
}

int	draw(t_ctx *ctx)
{
//	ft_bzero(ctx->img.addr, WIDTH * HEIGHT * 4);
//	print_background(ctx);
	raycasting_walls(ctx);
	mlx_put_image_to_window(&ctx->mlx, ctx->win, ctx->img.img, 0, 0);
	return (0);
}
