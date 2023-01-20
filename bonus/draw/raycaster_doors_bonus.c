#include "../structs_bonus.h"
#include "walls_bonus.h"

void	color_x_stripe_door(t_ctx *ctx, int x)
{
    double	step;
	double	tex_pos;
	int		y;
	int		color;

	step = 1.0 * ctx->tex.select_tex.tex_height / ctx->wall.line_height;
	tex_pos = (ctx->wall.draw_start - HEIGHT / 2 + ctx->wall.line_height / 2) * step;
    y = ctx->wall.draw_start - 1;
    while (++y < ctx->wall.draw_end)
    {
        ctx->tex.tex_y = (int)tex_pos & (ctx->tex.select_tex.tex_height - 1);
        tex_pos += step;
        color = (*(int*)(ctx->tex.select_tex.addr + (4 *
            ctx->tex.select_tex.tex_width * (int)ctx->tex.tex_y) + (4 *
                (int)ctx->tex.texX)));
        my_mlx_pixel_put(&ctx->img_door, x, y, color);
    }
	if (ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] == '1' ||
		ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] == 'D' ||
		(ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] == 'O' &&
		color == 0x261B1B))
    	ctx->sprites.z_buffer[x] = ctx->ray.perp_wall_dist;
}

int pos_door(char **map, int x, int y)
{
    if (map[y + 1][x] == 'D' || map[y - 1][x] == 'D' || map[y][x + 1] == 'D' ||
        map[y][x - 1] == 'D' || map[y + 1][x] == 'O' || map[y - 1][x] == 'O' ||
        map[y][x + 1] == 'O' || map[y][x - 1] == 'O')
    {
        if (map[y + 1][x] == 'D')
			map[y + 1][x] = 'O';
        else if (map[y + 1][x] == 'O')
			map[y + 1][x] = 'D';
        if (map[y - 1][x] == 'D')
			map[y - 1][x] = 'O';
        else if (map[y - 1][x] == 'O')
			map[y - 1][x] = 'D';
        if (map[y][x + 1] == 'D')
			map[y][x + 1] = 'O';
        else if (map[y][x + 1] == 'O')
			map[y][x + 1] = 'D';
        if (map[y][x - 1] == 'D')
			map[y][x - 1] = 'O';
        else if (map[y][x - 1] == 'O')
			map[y][x - 1] = 'D';
        return (1);
    }
    return (0);
}

void    init_tex_door(t_ctx *ctx)
{
    if (ctx->parse.map_door[ctx->ray.mapY][ctx->ray.mapX])
    {
        ctx->tex.select_tex = ctx->texture.tex_door[4];
        if (ctx->keys.key_door &&
            pos_door(ctx->parse.map, ctx->player.posX, ctx->player.posY))
            ctx->keys.key_door = false;
    }
    else
    {
        ctx->tex.select_tex = ctx->texture.tex_door[0];
        if (ctx->keys.key_door &&
            pos_door(ctx->parse.map, ctx->player.posX, ctx->player.posY))
            ctx->keys.key_door = false;
    }
}

void    draw_door(t_ctx *ctx, int x)
{
    init_tex_door(ctx);
	calc_wall_x(ctx);
	calc_x_coord_tex(ctx);
	color_x_stripe_door(ctx, x);
}

int	exec_dda_door(t_ctx *ctx)
{
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (ctx->ray.side_distX < ctx->ray.side_distY)
		{
			ctx->ray.side_distX += ctx->ray.delta_distX;
			ctx->ray.mapX += ctx->ray.stepX;
			ctx->ray.hit_side = 0;
		}
		else
		{
			ctx->ray.side_distY += ctx->ray.delta_distY;
			ctx->ray.mapY += ctx->ray.stepY;
			ctx->ray.hit_side = 1;			
		}
		if (ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] == '1')
        {
			hit = true;
            return (0);
        }
        else if (ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] == 'D')
        {
            hit = true;
            ctx->parse.map_door[ctx->ray.mapY][ctx->ray.mapX] = 1;
        }
        else if (ctx->parse.map[ctx->ray.mapY][ctx->ray.mapX] == 'O')
        {
            hit = true;
            ctx->parse.map_door[ctx->ray.mapY][ctx->ray.mapX] = 0;
        }
	}
    return (1);
}

void	raycasting_doors(t_ctx *ctx)
{
	int	x;
	
	x = -1;
	while (++x < WIDTH)
	{
		ctx->ray.cameraX = 2 * x / (double)WIDTH - 1;
		ctx->ray.ray_dirX = ctx->player.dirX + ctx->ray.plane_X * ctx->ray.cameraX;
		ctx->ray.ray_dirY = ctx->player.dirY + ctx->ray.plane_Y * ctx->ray.cameraX;
		ctx->ray.mapX = (int)ctx->player.posX;
		ctx->ray.mapY = (int)ctx->player.posY;
		if (ctx->ray.ray_dirX == 0)
			ctx->ray.delta_distX = 1e30;
		else
			ctx->ray.delta_distX = fabs(1 / ctx->ray.ray_dirX);
		if (ctx->ray.ray_dirY == 0)
			ctx->ray.delta_distY = 1e30;
		else
			ctx->ray.delta_distY = fabs(1 / ctx->ray.ray_dirY);
		calculate_side_dist(ctx);
		if (!exec_dda_door(ctx))
            continue ;
		calc_perp_wall_dist(ctx);
		calc_height_wall(ctx);
		draw_door(ctx, x);
	}
}
