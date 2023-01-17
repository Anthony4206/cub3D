#include "libft.h"
#include "../utils_bonus.h"
#include "../init_bonus.h"
#include "../structs_bonus.h"
#include "../parse/parse_bonus.h"
#include "walls_bonus.h"

int    is_sorted(t_sprites sprites)
{
    int i;

    i = -1;
    while (++i < sprites.num - 1)
    {
        if (sprites.sprite_distance[sprites.sprite_order[i]] 
			< sprites.sprite_distance[sprites.sprite_order[i + 1]])    
            return (0);
    }
    return (1);
}

//Sorts sprites from the furthest to the closest
void    sort_sprites(t_ctx *ctx)
{
    int     i;
    int     tmp;

    while (!is_sorted(ctx->sprites))
    {  
        i = -1;
        while (++i < ctx->sprites.num - 1)
        {
            if (ctx->sprites.sprite_distance[ctx->sprites.sprite_order[i]]
				< ctx->sprites.sprite_distance[ctx->sprites.sprite_order[i] + 1])
            {
                tmp = ctx->sprites.sprite_order[i]; 
                ctx->sprites.sprite_order[i] = ctx->sprites.sprite_order[i + 1];
                ctx->sprites.sprite_order[i + 1] = tmp;
            }
        }
    }
}

void	calc_order_sprite_dist(t_ctx *ctx)
{
	int i;

    i = -1;
    while (++i < ctx->sprites.num)
    {
        ctx->sprites.sprite_order[i] = i;
        ctx->sprites.sprite_distance[i] = ((ctx->player.posX - ctx->sprites.sprite[i].x)
        * (ctx->player.posX - ctx->sprites.sprite[i].x)
        + (ctx->player.posY - ctx->sprites.sprite[i].y) * (ctx->player.posY - ctx->sprites.sprite[i].y));
    }
}

//trans_y is actually the depth inside the screen, that what Z is in 3D
//using 'trans_y' instead of the real distance prevents fisheye
void	transform_sprite_coord(t_ctx *ctx, int i)
{
	double  inv_det;

	ctx->sprites.spriteX = ctx->sprites.sprite[ctx->sprites.sprite_order[i]].x - ctx->player.posX;
	ctx->sprites.spriteY = ctx->sprites.sprite[ctx->sprites.sprite_order[i]].y - ctx->player.posY;
	inv_det = 1.0 / (ctx->ray.plane_X * ctx->player.dirY - ctx->player.dirX * ctx->ray.plane_Y);
	ctx->sprites.trans_x = inv_det * (ctx->player.dirY * ctx->sprites.spriteX - ctx->player.dirX * ctx->sprites.spriteY);
	ctx->sprites.trans_y = inv_det * (-ctx->ray.plane_Y * ctx->sprites.spriteX + ctx->ray.plane_X * ctx->sprites.spriteY);
	ctx->sprites.screen_x = (int)((WIDTH / 2) * (1 + ctx->sprites.trans_x / ctx->sprites.trans_y));
	ctx->sprites.height = abs((int)(HEIGHT / ctx->sprites.trans_y));
}

void calc_draw_start_end(t_ctx *ctx)
{
	ctx->sprites.draw_start_y = -ctx->sprites.height / 2 + HEIGHT / 2;
	if(ctx->sprites.draw_start_y < 0)
		ctx->sprites.draw_start_y = 0;
	ctx->sprites.draw_end_y = ctx->sprites.height / 2 + HEIGHT / 2;
	if(ctx->sprites.draw_end_y >= HEIGHT)
		ctx->sprites.draw_end_y = HEIGHT - 1;
	ctx->sprites.width = abs( (int)(HEIGHT / (ctx->sprites.trans_y)));
	ctx->sprites.draw_start_x = -ctx->sprites.width / 2 + ctx->sprites.screen_x;
	if(ctx->sprites.draw_start_x < 0)
		ctx->sprites.draw_start_x = 0;
	ctx->sprites.draw_end_x = ctx->sprites.width / 2 + ctx->sprites.screen_x;
	if(ctx->sprites.draw_end_x >= WIDTH)
		ctx->sprites.draw_end_x = WIDTH - 1;
}

void	draw_stripes(t_ctx *ctx, int stripe)
{
	int				y;
	unsigned int	color;

	y = ctx->sprites.draw_start_y;
	while (++y < ctx->sprites.draw_end_y)
	{
		int d = (y) * 256 - HEIGHT * 128 + ctx->sprites.height * 128;
		// int texY = ((d * ctx->texture.sprites[ctx->sprites.sprite_order[i]].tex_height)
		int texY = ((d * ctx->texture.sprites[0][0].tex_height)
				/ ctx->sprites.height) / 256;
		//color = ctx->texture.sprites[ctx->sprites.sprite_order[i]].addr[ctx->texture.sprites[ctx->sprites.sprite_order[i]].tex_width
		// color = ctx->texture.sprites[0][0].addr[ctx->texture.sprites[0][0].tex_width
		// 		* texY + texX];
		color = (*(int*)(ctx->texture.sprites[0][0].addr + (4 * ctx->texture.sprites[0][0].tex_width * (int)texY) + (4 *
			(int)ctx->sprites.tex_x)));
		if((color & 0x00FFFFFF) != 0)
			ctx->screen.buffer[y][stripe] = color;
	}
}

//sprite[i] => ctx->sprite[i].addr
void    draw_sprite(t_ctx *ctx)
{
    int				i;
	int				stripe;

	calc_order_sprite_dist(ctx);
    sort_sprites(ctx);
    i = -1;
    while (++i < ctx->sprites.num)
    {
        transform_sprite_coord(ctx, i);
		calc_draw_start_end(ctx);
		stripe = ctx->sprites.draw_start_x;
        while (++stripe < ctx->sprites.draw_end_x)
        {
			//printf("TEST\n");
			fflush(stdout);
            //int texX = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screenX)) * ctx->texture.sprites[ctx->sprites.sprite_order[i]].tex_width / sprite_width) / 256;
			ctx->sprites.tex_x = (int)(256 * (stripe - (-ctx->sprites.width / 2 + ctx->sprites.screen_x))
					* ctx->texture.sprites[0][0].tex_width / ctx->sprites.width) / 256;
            if (ctx->sprites.trans_y > 0 && stripe > 0 && stripe < WIDTH
				&& ctx->sprites.trans_y < ctx->sprites.z_buffer[stripe])
				draw_stripes(ctx, stripe);
        }
    }
}