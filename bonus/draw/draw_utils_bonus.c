/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:13:32 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 15:12:24 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../structs_bonus.h"

void	calculate_delta(t_ctx *ctx)
{
	if (ctx->ray.ray_dir_x == 0)
		ctx->ray.delta_dist_x = 1e30;
	else
		ctx->ray.delta_dist_x = fabs(1 / ctx->ray.ray_dir_x);
	if (ctx->ray.ray_dir_y == 0)
		ctx->ray.delta_dist_y = 1e30;
	else
		ctx->ray.delta_dist_y = fabs(1 / ctx->ray.ray_dir_y);
}

int	ft_close(t_ctx *ctx)
{
	mlx_destroy_window(ctx->mlx, ctx->win);
	exit (EXIT_SUCCESS);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
