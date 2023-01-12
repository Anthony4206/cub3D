#include <libft.h>
#include "../structs.h"
#include "walls.h"

// void	player_moves(int keycode, t_ctx *ctx)
// {

// }

void	player_moves(int keycode, t_ctx *ctx)
{
	float	step;

	step = 1;
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
	// else if ((keycode >= 123 && keycode <= 126)
	// 	player_rotates(keycode, ctx);
	// else if (keycode >= 83 && keycode <= 92)
	// 	change_colors(keycode, global);
	// else if (keycode == 69 || keycode == 78)
	// 	zoom(keycode, global);
	// else if (keycode == 116 || keycode == 121 || keycode == 12 || keycode == 13)
	// 	change_z_factor(keycode, global);
	// else if ((keycode >= 6 && keycode <= 8) || (keycode <= 0 && keycode < 3))
	// 	rotation(keycode, global);
	// else if (keycode == 51)
	// 	reinitialize(keycode, global);
	// else if (keycode == 35)
	// 	change_projection_type(keycode, global);
	return (0);
}