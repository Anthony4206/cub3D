/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:45:57 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 14:49:21 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "structs_bonus.h"
#include "utils_bonus.h"

void	init_door_addr(t_ctx *ctx)
{
	ctx->texture.tex_door[0].addr = mlx_get_data_addr(
			ctx->texture.tex_door[0].img,
			&ctx->texture.tex_door[0].bpp, &ctx->texture.tex_door[0].line_len,
			&ctx->texture.tex_door[0].endian);
	ctx->texture.tex_door[4].addr = mlx_get_data_addr(
			ctx->texture.tex_door[4].img,
			&ctx->texture.tex_door[4].bpp, &ctx->texture.tex_door[4].line_len,
			&ctx->texture.tex_door[4].endian);
}

void	init_door_img(t_ctx *ctx)
{
	ctx->texture.tex_door[0].img = mlx_xpm_file_to_image(ctx->mlx,
			"./texture/doors/door_0.xpm", &ctx->texture.tex_door[0].tex_width,
			&ctx->texture.tex_door[0].tex_height);
	ctx->texture.tex_door[4].img = mlx_xpm_file_to_image(ctx->mlx,
			"./texture/doors/door_4.xpm", &ctx->texture.tex_door[4].tex_width,
			&ctx->texture.tex_door[4].tex_height);
	init_door_addr(ctx);
}
