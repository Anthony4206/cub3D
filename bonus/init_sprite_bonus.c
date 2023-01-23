/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:48:08 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 14:49:18 by alevasse         ###   ########.fr       */
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

void	parse_sprite(t_ctx *ctx)
{
	int	i;

	i = -1;
	ctx->sprites.sprite_path = malloc(sizeof(char *) * 5);
	ctx->sprites.sprite_path[0] = ft_strdup(
			"./texture/sprites/Explosion_1.xpm");
	ctx->sprites.sprite_path[1] = ft_strdup(
			"./texture/sprites/Explosion_2.xpm");
	ctx->sprites.sprite_path[2] = ft_strdup(
			"./texture/sprites/Explosion_3.xpm");
	ctx->sprites.sprite_path[3] = ft_strdup(
			"./texture/sprites/Explosion_4.xpm");
	ctx->sprites.sprite_path[4] = ft_strdup(
			"./texture/sprites/Explosion_1.xpm");
	while (++i < 5)
	{
		if (open(ctx->sprites.sprite_path[i], O_RDONLY) < 0)
			error_exit("Error\nInvalid sprite texture path.\n");
	}
}

void	init_sprites_img(t_ctx *ctx)
{
	int	i;

	i = -1;
	ctx->texture.sprites = malloc(sizeof(t_data) * 5);
	while (++i < 5)
	{
		ctx->texture.sprites[i].img = mlx_xpm_file_to_image(ctx->mlx,
				ctx->sprites.sprite_path[i], &ctx->texture.sprites[i].tex_width,
				&ctx->texture.sprites[i].tex_height);
		ctx->texture.sprites[i].addr = mlx_get_data_addr(
				ctx->texture.sprites[i].img,
				&ctx->texture.sprites[i].bpp, &ctx->texture.sprites[i].line_len,
				&ctx->texture.sprites[i].endian);
	}
}

void	get_sprites_coord(t_ctx *ctx)
{
	int	y;
	int	x;
	int	i;

	y = -1;
	i = 0;
	ctx->sprites.sprite = malloc(sizeof(t_coord) * ctx->sprites.num);
	while (ctx->parse.map[++y])
	{
		x = -1;
		while (ctx->parse.map[y][++x])
		{
			if (ft_strchr("A", ctx->parse.map[y][x]))
			{
				ctx->sprites.sprite[i].x = x + 0.5;
				ctx->sprites.sprite[i].y = y + 0.5;
				i++;
			}
		}
	}
}

void	init_sprite(t_ctx *ctx)
{
	ctx->sprites.num = ctx->parse.sprites_num;
	get_sprites_coord(ctx);
	ctx->sprites.z_buffer = malloc(sizeof(double) * WIDTH);
	ctx->sprites.order = malloc(sizeof(int) * ctx->sprites.num);
	ctx->sprites.sprite_distance = malloc(sizeof(double) * ctx->sprites.num);
}
