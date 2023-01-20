#include <libft.h>
#include "../structs_bonus.h"
#include "walls_bonus.h"

int	check_new_pos(t_ctx *ctx)
{
	double	r;
	float	x;
	float	y;

	r = 0.2;
	x = ctx->player.posX + r;
	y = ctx->player.posY;
	while (x > ctx->player.posX)
	{
		x -= 0.000001;
		y -= 0.000001;
		if (ctx->parse.map[(int)y][(int)x] == '1'
		|| ctx->parse.map[(int)y][(int)x] == 'D'
		|| ctx->parse.map[(int)y][(int)x] == 'A')
			return (0);
	}
	while (x > ctx->player.posX - r)
	{
		x -= 0.000001;
		y += 0.000001;
		if (ctx->parse.map[(int)y][(int)x] == '1'
		|| ctx->parse.map[(int)y][(int)x] == 'D'
		|| ctx->parse.map[(int)y][(int)x] == 'A')
			return (0);
	}
		while (x < ctx->player.posX)
	{
		x += 0.000001;
		y += 0.000001;
		if (ctx->parse.map[(int)y][(int)x] == '1'
		|| ctx->parse.map[(int)y][(int)x] == 'D'
		|| ctx->parse.map[(int)y][(int)x] == 'A')
			return (0);
	}
	while (x < ctx->player.posX + r)
	{
		x += 0.000001;
		y -= 0.000001;
		if (ctx->parse.map[(int)y][(int)x] == '1'
		|| ctx->parse.map[(int)y][(int)x] == 'D'
		|| ctx->parse.map[(int)y][(int)x] == 'A')
			return (0);
	}
	return (1);
}

int	check_sliding_ag_walls(t_ctx *ctx, float step)
{
	if (ctx->keys.key_w == true)
	{
		if (ctx->player.dirX == 0 || ctx->player.dirY == 0)
			return (0);
		if (ctx->player.dirX < 0 && ctx->player.dirY < 0)
		{
			ctx->player.posX = ctx->player.posX - step;
			if (check_new_pos(ctx))
				return (1);
			ctx->player.posX = ctx->player.posX + step;
			ctx->player.posY = ctx->player.posY - step;
			if (!check_new_pos(ctx))
				return (0);
		}
		else if (ctx->player.dirX > 0 && ctx->player.dirY < 0)
		{
			ctx->player.posX = ctx->player.posX + step;
			if (check_new_pos(ctx))
				return (1);
			ctx->player.posX = ctx->player.posX - step;
			ctx->player.posY = ctx->player.posY - step;
			if (!check_new_pos(ctx))
				return (0);
		}
		else if (ctx->player.dirX > 0 && ctx->player.dirY > 0)
		{
			ctx->player.posX = ctx->player.posX + step;
			if (check_new_pos(ctx))
				return (1);
			ctx->player.posX = ctx->player.posX - step;
			ctx->player.posY = ctx->player.posY + step;
			if (!check_new_pos(ctx))
				return (0);
		}
		else if (ctx->player.dirX < 0 && ctx->player.dirY > 0)
		{
			ctx->player.posX = ctx->player.posX - step;
			if (check_new_pos(ctx))
				return (1);
			ctx->player.posX = ctx->player.posX + step;
			ctx->player.posY = ctx->player.posY + step;
			if (!check_new_pos(ctx))
				return (0);
		}
		return (1);
	}
	return (1);
}

void	player_moves(t_ctx *ctx)
{
	float	step;
	float	old_pos_x;
	float	old_pos_y;

	step = 0.08;
	old_pos_x = ctx->player.posX;
	old_pos_y = ctx->player.posY;
	if (ctx->keys.key_w == true)
	{
		ctx->player.posX = ctx->player.posX + (ctx->player.dirX * step);
		ctx->player.posY = ctx->player.posY + (ctx->player.dirY * step);
	}
	else if (ctx->keys.key_s == true)
	{
		ctx->player.posX = ctx->player.posX - (ctx->player.dirX * step);
		ctx->player.posY = ctx->player.posY - (ctx->player.dirY * step);
	}	
	else if (ctx->keys.key_d == true)
	{
		ctx->player.posX = ctx->player.posX - (ctx->player.dirY * step);
		ctx->player.posY = ctx->player.posY + (ctx->player.dirX * step);
	}
	else if (ctx->keys.key_a == true)
	{
		ctx->player.posX = ctx->player.posX + (ctx->player.dirY * step);
		ctx->player.posY = ctx->player.posY - (ctx->player.dirX * step);
	}
	if (!check_new_pos(ctx))
	{
		ctx->player.posX = old_pos_x;
		ctx->player.posY = old_pos_y;
		if (!(check_sliding_ag_walls(ctx, step)))
		{
			ctx->player.posX = old_pos_x;
			ctx->player.posY = old_pos_y;
		}
	}
}

void	player_rotates(t_ctx *ctx)
{
	float	a;
	double	tmp_x;
	double	tmp_plane_x;

	a = 0;
	if (ctx->keys.key_left == true)
	{
		a = -0.05;
		tmp_x = ctx->player.dirX * cos(a) + ctx->player.dirY * (-sin(a));
		ctx->player.dirY = ctx->player.dirX * sin(a) + ctx->player.dirY * (cos(a));
		ctx->player.dirX = tmp_x;
		tmp_plane_x = ctx->ray.plane_X * cos(a) - ctx->ray.plane_Y * sin(a);
		ctx->ray.plane_Y =ctx->ray.plane_X * sin(a) + ctx->ray.plane_Y * cos(a);
		ctx->ray.plane_X = tmp_plane_x;
	}
	else if (ctx->keys.key_right == true)
	{
		a = 0.05;
		tmp_x = ctx->player.dirX * cos(a) + ctx->player.dirY * (-sin(a));
		ctx->player.dirY = ctx->player.dirX * sin(a) + ctx->player.dirY * (cos(a));
		ctx->player.dirX = tmp_x;
		tmp_plane_x = ctx->ray.plane_X * cos(a) - ctx->ray.plane_Y * sin(a);
		ctx->ray.plane_Y =ctx->ray.plane_X * sin(a) + ctx->ray.plane_Y * cos(a);
		ctx->ray.plane_X = tmp_plane_x;
	}
}