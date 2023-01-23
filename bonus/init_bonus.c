/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:31:42 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 14:52:02 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <fcntl.h>
#include "init_bonus.h"
#include "utils_bonus.h"
#include "structs_bonus.h"
#include "parse/parse_bonus.h"
#include "draw/draw_bonus.h"

void	init_plane(t_ctx *ctx)
{
	if (ctx->parse.init_dir == 'N' || ctx->parse.init_dir == 'S')
	{
		ctx->ray.plane_x = 0.66;
		ctx->ray.plane_y = 0.0;
	}
	else
	{
		ctx->ray.plane_x = 0;
		ctx->ray.plane_y = 0.66;
	}
}

void	init_player(t_ctx *ctx)
{
	ctx->player.pos_x = ctx->parse.init_pos_x + 0.55;
	ctx->player.pos_y = ctx->parse.init_pos_y + 0.55;
	if (ctx->parse.init_dir == 'N' || ctx->parse.init_dir == 'S')
		ctx->player.dir_x = 0;
	else if (ctx->parse.init_dir == 'E')
		ctx->player.dir_x = 1;
	else
		ctx->player.dir_x = -1;
	if (ctx->parse.init_dir == 'E' || ctx->parse.init_dir == 'W')
		ctx->player.dir_y = 0;
	else if (ctx->parse.init_dir == 'S')
		ctx->player.dir_y = 1;
	else
		ctx->player.dir_y = -1;
}

void	init_mlx(t_ctx *ctx)
{
	ctx->mlx = mlx_init();
	ctx->win = mlx_new_window(ctx->mlx, WIDTH, HEIGHT, "cub3d");
	ctx->img.img = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	ctx->img.addr = mlx_get_data_addr(ctx->img.img, &ctx->img.bpp,
			&ctx->img.line_len, &ctx->img.endian);
	ctx->img_door.img = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	ctx->img_door.addr = mlx_get_data_addr(ctx->img_door.img,
			&ctx->img_door.bpp, &ctx->img_door.line_len, &ctx->img_door.endian);
	ctx->img_sprite.img = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	ctx->img_sprite.addr = mlx_get_data_addr(ctx->img_sprite.img,
			&ctx->img_sprite.bpp, &ctx->img_sprite.line_len,
			&ctx->img_sprite.endian);
}

void	init_texture_img(t_ctx *ctx)
{
	ctx->texture.n_wall.img = mlx_xpm_file_to_image(ctx->mlx,
			ctx->parse.n, &ctx->texture.n_wall.tex_width,
			&ctx->texture.n_wall.tex_height);
	ctx->texture.n_wall.addr = mlx_get_data_addr(ctx->texture.n_wall.img,
			&ctx->texture.n_wall.bpp, &ctx->texture.n_wall.line_len,
			&ctx->texture.n_wall.endian);
	ctx->texture.s_wall.img = mlx_xpm_file_to_image(ctx->mlx,
			ctx->parse.s, &ctx->texture.s_wall.tex_width,
			&ctx->texture.s_wall.tex_height);
	ctx->texture.s_wall.addr = mlx_get_data_addr(ctx->texture.s_wall.img,
			&ctx->texture.s_wall.bpp, &ctx->texture.s_wall.line_len,
			&ctx->texture.s_wall.endian);
	ctx->texture.e_wall.img = mlx_xpm_file_to_image(ctx->mlx,
			ctx->parse.e, &ctx->texture.e_wall.tex_width,
			&ctx->texture.e_wall.tex_height);
	ctx->texture.e_wall.addr = mlx_get_data_addr(ctx->texture.e_wall.img,
			&ctx->texture.e_wall.bpp, &ctx->texture.e_wall.line_len,
			&ctx->texture.e_wall.endian);
	ctx->texture.w_wall.img = mlx_xpm_file_to_image(ctx->mlx,
			ctx->parse.w, &ctx->texture.w_wall.tex_width,
			&ctx->texture.w_wall.tex_height);
	ctx->texture.w_wall.addr = mlx_get_data_addr(ctx->texture.w_wall.img,
			&ctx->texture.w_wall.bpp, &ctx->texture.w_wall.line_len,
			&ctx->texture.w_wall.endian);
	init_door_img(ctx);
}

void	init_cub(t_ctx *ctx)
{
	init_player(ctx);
	init_plane(ctx);
	init_mlx(ctx);
	init_texture_img(ctx);
	parse_sprite(ctx);
	init_sprites_img(ctx);
	init_mini_map(ctx);
	init_screen_buffer(ctx);
	init_sprite(ctx);
	ctx->time.init_time = get_time();
}
