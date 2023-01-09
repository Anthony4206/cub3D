/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:31:42 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/29 16:00:13 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "structs.h"
#include "parse/parse.h"

void	init_player(t_ctx *ctx)
{
	ctx->player.posX = ctx->parse.init_posX;
	ctx->player.posY = ctx->parse.init_posY;
	if (ctx->parse.init_dir == 'N' || ctx->parse.init_dir == 'S')
		ctx->player.dirX = 0;
	else if (ctx->parse.init_dir == 'E')
		ctx->player.dirX = 1;
	else
		ctx->player.dirX = -1;
	if (ctx->parse.init_dir == 'E' || ctx->parse.init_dir == 'W')
		ctx->player.dirY = 0;
	else if (ctx->parse.init_dir == 'S')
		ctx->player.dirY = 1;
	else
		ctx->player.dirY = -1;
	ctx->ray.plane_X = 0;
	ctx->ray.plane_Y = 0.66;
}

void    init_mlx(t_ctx *ctx)
{
    ctx->mlx = mlx_init();
    ctx->win = mlx_new_window(ctx->mlx, WIGHT, HEIGHT, "cub3d");
    ctx->img.img = mlw_new_img(ctx->mlx, WIGHT, HEIGHT);
    ctx->img.addr = mlx_get_data_addr(ctx->img.img, &ctx->img.bpp,
            &ctx->img.line_len, &ctx->img.endian);
}

void    init_texture(t_ctx *ctx)
{
    int wight_img;
    int height_img;

    ctx->
}

void	init_cub(t_ctx *ctx)
{
	init_player(ctx);
	init_mlx(ctx);
	init_texture(ctx);
	 * initialiser img
	 * initialiser addr
	 * initialiser texture
	 * initialiser addr texture

}
