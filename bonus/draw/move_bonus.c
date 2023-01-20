#include <libft.h>
#include "../structs_bonus.h"
#include "walls_bonus.h"

void	player_moves(t_ctx *ctx)
{
	float	step;
	float	old_pos_x;
	float	old_pos_y;

	step = 0.05;
	old_pos_x = ctx->player.posX;
	old_pos_y = ctx->player.posY;
	if (ctx->keys.key_w == true)
	{
		ctx->player.posX = ctx->player.posX + (ctx->player.dirX * step);
		ctx->player.posY = ctx->player.posY + (ctx->player.dirY * step);
	}
	if (ctx->keys.key_s == true)
	{
		ctx->player.posX = ctx->player.posX - (ctx->player.dirX * step);
		ctx->player.posY = ctx->player.posY - (ctx->player.dirY * step);
	}	
	if (ctx->keys.key_d == true)
	{
		ctx->player.posX = ctx->player.posX - (ctx->player.dirY * step);
		ctx->player.posY = ctx->player.posY + (ctx->player.dirX * step);
	}
	if (ctx->keys.key_a == true)
	{
		ctx->player.posX = ctx->player.posX + (ctx->player.dirY * step);
		ctx->player.posY = ctx->player.posY - (ctx->player.dirX * step);
	}
	if (ctx->parse.map[(int)ctx->player.posY][(int)ctx->player.posX] - '0' == 1 ||
        ctx->parse.map[(int)ctx->player.posY][(int)ctx->player.posX] == 'D')
	{
		ctx->player.posX = old_pos_x;
		ctx->player.posY = old_pos_y;
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
		a = -0.03;
		tmp_x = ctx->player.dirX * cos(a) + ctx->player.dirY * (-sin(a));
		ctx->player.dirY = ctx->player.dirX * sin(a) + ctx->player.dirY * (cos(a));
		ctx->player.dirX = tmp_x;
		tmp_plane_x = ctx->ray.plane_X * cos(a) - ctx->ray.plane_Y * sin(a);
		ctx->ray.plane_Y =ctx->ray.plane_X * sin(a) + ctx->ray.plane_Y * cos(a);
		ctx->ray.plane_X = tmp_plane_x;
	}
	else if (ctx->keys.key_right == true)
	{
		a = 0.03;
		tmp_x = ctx->player.dirX * cos(a) + ctx->player.dirY * (-sin(a));
		ctx->player.dirY = ctx->player.dirX * sin(a) + ctx->player.dirY * (cos(a));
		ctx->player.dirX = tmp_x;
		tmp_plane_x = ctx->ray.plane_X * cos(a) - ctx->ray.plane_Y * sin(a);
		ctx->ray.plane_Y =ctx->ray.plane_X * sin(a) + ctx->ray.plane_Y * cos(a);
		ctx->ray.plane_X = tmp_plane_x;
	}
}