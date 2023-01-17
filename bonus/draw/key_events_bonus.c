#include <libft.h>
#include <math.h>
#include "../structs_bonus.h"
#include "walls_bonus.h"

int	release_key(int key, void *param)
{
    t_ctx	*ctx;

    ctx = (t_ctx *)param;
    if (key == 13)
 		ctx->keys.key_w = false;
	else if (key == 0)
		ctx->keys.key_a = false;
	else if (key == 1)
 		ctx->keys.key_s = false;
	else if (key == 2)
 		ctx->keys.key_d = false;
	else if (key == 123)
 		ctx->keys.key_left = false;
	else if (key == 124)
 		ctx->keys.key_right = false;
	//printf("keycode = %d is released\n", key);
    return (0);
}

void	end_program(t_ctx *ctx)
{
	(void)ctx;
	//free ce qu'il faut
}

int	press_key(int key, void *param)
{
	 t_ctx	*ctx;

    ctx = (t_ctx *)param;
	if (key == 53)
	{
		mlx_destroy_window(ctx->mlx, ctx->win);
		end_program(ctx);
		exit(EXIT_SUCCESS);
	}
	 else if (key == 13)
 		ctx->keys.key_w = true;
	else if (key == 0)
 		ctx->keys.key_a = true;
	else if (key == 1)
 		ctx->keys.key_s = true;
	else if (key == 2)
 		ctx->keys.key_d = true;
	else if (key == 123)
 		ctx->keys.key_left = true;
	else if (key == 124)
 		ctx->keys.key_right = true;
	return (0);
}