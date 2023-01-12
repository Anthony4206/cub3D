/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:31:42 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/09 10:05:19 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include "init.h"
#include "utils.h"
#include "structs.h"
#include "parse/parse.h"
#include "draw/walls.h"

void	init_plane(t_ctx *ctx)
{
	if (ctx->parse.init_dir == 'N' || ctx->parse.init_dir == 'S')
	{
		ctx->ray.plane_X = 0.66;
		ctx->ray.plane_Y = 0.0;
	}
	else
	{
		ctx->ray.plane_X = 0;
		ctx->ray.plane_Y = 0.66;
	}
}

void	init_player(t_ctx *ctx)
{
	ctx->player.posX = ctx->parse.init_posX + 0.5;
	ctx->player.posY = ctx->parse.init_posY + 0.5;
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
}

void    init_mlx(t_ctx *ctx)
{
	ctx->mlx = mlx_init();
	ctx->win = mlx_new_window(ctx->mlx, WIDTH, HEIGHT, "cub3d");
	ctx->img.img = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	ctx->img.addr = mlx_get_data_addr(ctx->img.img, &ctx->img.bpp,
			&ctx->img.line_len, &ctx->img.endian);
}

void    init_texture_img(t_ctx *ctx)
{
	ctx->texture.N_wall.img = mlx_xpm_file_to_image(ctx->mlx,
			ctx->parse.N, &ctx->tex.tex_width, &ctx->tex.tex_height);
	ctx->texture.N_wall.addr = mlx_get_data_addr(ctx->texture.N_wall.img,
			&ctx->texture.N_wall.bpp, &ctx->texture.N_wall.line_len,
			&ctx->texture.N_wall.endian);
	ctx->texture.S_wall.img = mlx_xpm_file_to_image(ctx->mlx,
			ctx->parse.S, &ctx->texture.S_wall.tex_width,
                &ctx->texture.S_wall.tex_height);	
	ctx->texture.S_wall.addr = mlx_get_data_addr(ctx->texture.S_wall.img,
			&ctx->texture.S_wall.bpp, &ctx->texture.S_wall.line_len,
			&ctx->texture.S_wall.endian);
	ctx->texture.E_wall.img = mlx_xpm_file_to_image(ctx->mlx,
			ctx->parse.E, &ctx->texture.E_wall.tex_width, &ctx->texture.E_wall.tex_height);	
	ctx->texture.E_wall.addr = mlx_get_data_addr(ctx->texture.E_wall.img,
			&ctx->texture.E_wall.bpp, &ctx->texture.E_wall.line_len,
			&ctx->texture.E_wall.endian);
	ctx->texture.W_wall.img = mlx_xpm_file_to_image(ctx->mlx,
			ctx->parse.W, &ctx->texture.W_wall.tex_width, &ctx->texture.W_wall.tex_height);
	ctx->texture.W_wall.addr = mlx_get_data_addr(ctx->texture.W_wall.img,
			&ctx->texture.W_wall.bpp, &ctx->texture.W_wall.line_len,
			&ctx->texture.W_wall.endian);
}

void	init_screen_buffer(t_ctx *ctx)
{
	int y = -1;

	ctx->screen.buffer = ft_calloc(sizeof(unsigned int *), HEIGHT);
	while (++y < HEIGHT)
		ctx->screen.buffer[y] = ft_calloc(sizeof(unsigned int), WIDTH);
}

void	init_cub(t_ctx *ctx)
{
	init_player(ctx);
	init_plane(ctx);
	init_mlx(ctx);
	init_texture_img(ctx);
	generate_texture(ctx);
	init_screen_buffer(ctx);
}
