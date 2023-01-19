#include "libft.h"
#include "../utils_bonus.h"
#include "../init_bonus.h"
#include "../structs_bonus.h"
#include "../parse/parse_bonus.h"
#include "walls_bonus.h"

int	sprites_are_sorted(t_sprites sprites)
{
	int	i;

	i = -1;
	while (++i < sprites.num - 1)
	{
		if (sprites.sprite_distance[sprites.order[i]]
			< sprites.sprite_distance[sprites.order[i + 1]])
			return (0);
	}
	return (1);
}

//Sorts sprites from the furthest to the closest
void	sort_sprites(t_ctx *ctx)
{
	int	i;
	int	tmp;

	while (!sprites_are_sorted(ctx->sprites))
	{
		i = -1;
		while (++i < ctx->sprites.num - 1)
		{
			if (ctx->sprites.sprite_distance[ctx->sprites.order[i]]
				< ctx->sprites.sprite_distance[ctx->sprites.order[i + 1]])
			{
				tmp = ctx->sprites.order[i];
				ctx->sprites.order[i] = ctx->sprites.order[i + 1];
				ctx->sprites.order[i + 1] = tmp;
			}
		}
	}
}

void	calc_order_sprite_dist(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->sprites.num)
	{
		ctx->sprites.order[i] = i;
		ctx->sprites.sprite_distance[i] = ((ctx->player.posX
					- ctx->sprites.sprite[i].x)
				* (ctx->player.posX - ctx->sprites.sprite[i].x)
				+ (ctx->player.posY - ctx->sprites.sprite[i].y)
				* (ctx->player.posY - ctx->sprites.sprite[i].y));
	}
}

//trans_y is actually the depth inside the screen, that what Z is in 3D
//using 'trans_y' instead of the real distance prevents fisheye
void	transform_sprite_coord(t_ctx *ctx, int i)
{
	double	inv_det;

	ctx->sprites.spriteX = ctx->sprites.sprite[ctx->sprites.order[i]].x
		- ctx->player.posX;
	ctx->sprites.spriteY = ctx->sprites.sprite[ctx->sprites.order[i]].y
		- ctx->player.posY;
	inv_det = 1.0 / (ctx->ray.plane_X * ctx->player.dirY
			- ctx->player.dirX * ctx->ray.plane_Y);
	ctx->sprites.trans_x = inv_det * (ctx->player.dirY * ctx->sprites.spriteX
			- ctx->player.dirX * ctx->sprites.spriteY);
	ctx->sprites.trans_y = inv_det * (-ctx->ray.plane_Y * ctx->sprites.spriteX
			+ ctx->ray.plane_X * ctx->sprites.spriteY);
	ctx->sprites.screen_x = (int)((WIDTH / 2) * (1 + ctx->sprites.trans_x
				/ ctx->sprites.trans_y));
	ctx->sprites.height = abs((int)(HEIGHT / ctx->sprites.trans_y));
}