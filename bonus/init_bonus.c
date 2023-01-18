/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:31:42 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/16 06:54:11 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>

#include "init_bonus.h"
#include "utils_bonus.h"
#include "structs_bonus.h"
#include "parse/parse_bonus.h"
#include "draw/walls_bonus.h"

//tv_sec = seconds, tv.usec = micro seconds;
//gettimeofday: returns time in microseconds
//init_time returns time in milliseconds
int	get_time(void)
{
	struct timeval	cur_time;
	unsigned int	time;

	gettimeofday(&cur_time, NULL);
	time = (cur_time.tv_sec * 1000000) + cur_time.tv_usec;
	return (time);
}


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
	ctx->player.posX = ctx->parse.init_posX + 0.55;
	ctx->player.posY = ctx->parse.init_posY + 0.55;
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
			ctx->parse.N, &ctx->texture.N_wall.tex_width, &ctx->texture.N_wall.tex_height);
	ctx->texture.N_wall.addr = mlx_get_data_addr(ctx->texture.N_wall.img,
			&ctx->texture.N_wall.bpp, &ctx->texture.N_wall.line_len,
			&ctx->texture.N_wall.endian);
	ctx->texture.S_wall.img = mlx_xpm_file_to_image(ctx->mlx,
			ctx->parse.S, &ctx->texture.S_wall.tex_width, &ctx->texture.S_wall.tex_height);	
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

void	init_sprites_img(t_ctx *ctx)
{
	ctx->texture.sprites = malloc(sizeof(t_data *) * 2);
	ctx->texture.sprites[0] = malloc(sizeof(t_data) * 5);
	ctx->texture.sprites[1] = malloc(sizeof(t_data) * 5);

	ctx->texture.sprites[0][0].img = mlx_xpm_file_to_image(ctx->mlx,
		"./texture/sprites/Explosion_5.xpm", &ctx->texture.sprites[0][0].tex_width, &ctx->texture.sprites[0][0].tex_height);
	ctx->texture.sprites[0][0].addr = mlx_get_data_addr(ctx->texture.sprites[0][0].img,
			&ctx->texture.sprites[0][0].bpp, &ctx->texture.sprites[0][0].line_len,
			&ctx->texture.sprites[0][0].endian);
	ctx->texture.sprites[0][1].img = mlx_xpm_file_to_image(ctx->mlx,
		"./texture/sprites/Explosion_6.xpm", &ctx->texture.sprites[0][1].tex_width, &ctx->texture.sprites[0][1].tex_height);
	ctx->texture.sprites[0][1].addr = mlx_get_data_addr(ctx->texture.sprites[0][1].img,
			&ctx->texture.sprites[0][1].bpp, &ctx->texture.sprites[0][1].line_len,
			&ctx->texture.sprites[0][1].endian);
}

void	init_screen_buffer(t_ctx *ctx)
{
	int y = -1;

	ctx->screen.buffer = ft_calloc(sizeof(unsigned int *), HEIGHT);
	while (++y < HEIGHT)
		ctx->screen.buffer[y] = ft_calloc(sizeof(unsigned int), WIDTH);
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

void    init_sprite(t_ctx *ctx)
{
    //on parse la map pour lister les sprites et renseigner leurs données
    //on initialise les structs t_sprite
    ctx->sprites.num = ctx->parse.sprites_num;
    get_sprites_coord(ctx);
    ctx->sprites.z_buffer = malloc(sizeof(double) * WIDTH);
    ctx->sprites.sprite_order = malloc(sizeof(int) * ctx->sprites.num);
    ctx->sprites.sprite_distance = malloc(sizeof(double) * ctx->sprites.num);
    //fonction pour trier les sprites par ordre d'éloignement
    //fonction pour initialiser les textures
}

void	init_cub(t_ctx *ctx)
{
	init_player(ctx);
	init_plane(ctx);
	init_mlx(ctx);
	init_texture_img(ctx);
	init_sprites_img(ctx);
    init_mini_map(ctx);
	init_screen_buffer(ctx);
	init_sprite(ctx);
	ctx->time.init_time = get_time();
}

void    init_door_img()
{
    //initialiser image
}