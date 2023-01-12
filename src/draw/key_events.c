#include <libft.h>
#include "../structs.h"
#include "walls.h"

void	player_move(int keycode, t_ctx *ctx)
{
	if (keycode == 125)
		ctx->player.posX -= 1;
	else if (keycode == 126)
		ctx->player.posX += 1;
	else if (keycode == 123)
		ctx->player.posY -= 1;
	else if (keycode == 124)
		ctx->player.posY += 1;
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
	if (keycode == 53)
	{
		mlx_destroy_window(ctx->mlx, ctx->win);
		end_program(ctx);
		exit(EXIT_SUCCESS);
	}
	else if (keycode >= 123 && keycode <= 126)
		player_move(keycode, ctx);
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