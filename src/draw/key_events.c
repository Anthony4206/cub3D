#include <libft.h>
#include "../structs.h"
#include "walls.h"

void	player_moves(int keycode, t_ctx *ctx)
{
	float	step;
	float	old_pos_x;
	float	old_pos_y;

	step = 0.3;
	old_pos_x = ctx->player.posX;
	old_pos_y = ctx->player.posY;
	if (keycode == 13)
	{
		ctx->player.posX = ctx->player.posX + (ctx->player.dirX * step);
		ctx->player.posY = ctx->player.posY + (ctx->player.dirY * step);
	}
	else if (keycode == 1)
	{
		ctx->player.posX = ctx->player.posX - (ctx->player.dirX * step);
		ctx->player.posY = ctx->player.posY - (ctx->player.dirY * step);
	}
	else if (keycode == 2)
	{
		ctx->player.posX = ctx->player.posX - (ctx->player.dirY * step);
		ctx->player.posY = ctx->player.posY + (ctx->player.dirX * step);
	}
	else if (keycode == 0)
	{
		ctx->player.posX = ctx->player.posX + (ctx->player.dirY * step);
		ctx->player.posY = ctx->player.posY - (ctx->player.dirX * step);
	}
	if (ctx->parse.map[(int)ctx->player.posY][(int)ctx->player.posX] - '0' > 0)
	{
		ctx->player.posX = old_pos_x;
		ctx->player.posY = old_pos_y;
	}
	ft_bzero(ctx->img.addr, HEIGHT * ctx->img.line_len); //reset the already colored pixels (all bytes)
	draw(ctx);
}

void	player_rotates(int keycode, t_ctx *ctx)
{
	float	a;
	double	tmp_x;
	double	tmp_plane_x;

	a = 0;
	if (keycode == 123)
	{
		a = -0.1;
		tmp_x = ctx->player.dirX * cos(a) + ctx->player.dirY * (-sin(a));
		ctx->player.dirY = ctx->player.dirX * sin(a) + ctx->player.dirY * (cos(a));
		ctx->player.dirX = tmp_x;
		tmp_plane_x = ctx->ray.plane_X * cos(a) - ctx->ray.plane_Y * sin(a);
		ctx->ray.plane_Y =ctx->ray.plane_X * sin(a) + ctx->ray.plane_Y * cos(a);
		ctx->ray.plane_X = tmp_plane_x;
	}
	else if (keycode == 124)
	{
		a = 0.1;
		tmp_x = ctx->player.dirX * cos(a) + ctx->player.dirY * (-sin(a));
		ctx->player.dirY = ctx->player.dirX * sin(a) + ctx->player.dirY * (cos(a));
		ctx->player.dirX = tmp_x;
		tmp_plane_x = ctx->ray.plane_X * cos(a) - ctx->ray.plane_Y * sin(a);
		ctx->ray.plane_Y =ctx->ray.plane_X * sin(a) + ctx->ray.plane_Y * cos(a);
		ctx->ray.plane_X = tmp_plane_x;
	}
	
	ft_bzero(ctx->img.addr, HEIGHT * ctx->img.line_len); //reset the already colored pixels (all bytes)
	draw(ctx);
}

void	end_program(t_ctx *ctx)
{
	(void)ctx;
	//free ce qu'il faut
}

int	deal_key(int keycode, t_ctx *ctx)
{
	//printf("Keycode = %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(ctx->mlx, ctx->win);
		end_program(ctx);
		exit(EXIT_SUCCESS);
	}
	else if ((keycode >= 0 && keycode <= 2) || keycode == 13)
		player_moves(keycode, ctx);
	else if (keycode >= 123 && keycode <= 124)
		player_rotates(keycode, ctx);
	return (0);
}