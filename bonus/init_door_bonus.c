#include <fcntl.h>

#include "structs_bonus.h"
#include "utils_bonus.h"

void    init_door_addr(t_ctx *ctx)
{
    ctx->texture.tex_door[0].addr = mlx_get_data_addr(ctx->texture.tex_door[0].img,
        &ctx->texture.tex_door[0].bpp, &ctx->texture.tex_door[0].line_len,
        &ctx->texture.tex_door[0].endian);
    ctx->texture.tex_door[1].addr = mlx_get_data_addr(ctx->texture.tex_door[1].img,
        &ctx->texture.tex_door[1].bpp, &ctx->texture.tex_door[1].line_len,
        &ctx->texture.tex_door[1].endian);
    ctx->texture.tex_door[2].addr = mlx_get_data_addr(ctx->texture.tex_door[2].img,
        &ctx->texture.tex_door[2].bpp, &ctx->texture.tex_door[2].line_len,
        &ctx->texture.tex_door[2].endian); 
	ctx->texture.tex_door[3].addr = mlx_get_data_addr(ctx->texture.tex_door[3].img,
        &ctx->texture.tex_door[3].bpp, &ctx->texture.tex_door[3].line_len,
        &ctx->texture.tex_door[3].endian);
    ctx->texture.tex_door[4].addr = mlx_get_data_addr(ctx->texture.tex_door[4].img,
        &ctx->texture.tex_door[4].bpp, &ctx->texture.tex_door[4].line_len,
        &ctx->texture.tex_door[4].endian);
}

void    init_door_img(t_ctx * ctx)
{
    ctx->texture.tex_door[0].img = mlx_xpm_file_to_image(ctx->mlx,
        "./texture/doors/door_0.xpm", &ctx->texture.tex_door[0].tex_width,
        &ctx->texture.tex_door[0].tex_height);
	ctx->texture.tex_door[1].img = mlx_xpm_file_to_image(ctx->mlx,
        "./texture/doors/door_1.xpm", &ctx->texture.tex_door[1].tex_width,
        &ctx->texture.tex_door[1].tex_height);
	ctx->texture.tex_door[2].img = mlx_xpm_file_to_image(ctx->mlx,
        "./texture/doors/door_2.xpm", &ctx->texture.tex_door[2].tex_width,
        &ctx->texture.tex_door[2].tex_height);	
	ctx->texture.tex_door[3].img = mlx_xpm_file_to_image(ctx->mlx,
        "./texture/doors/door_3.xpm", &ctx->texture.tex_door[3].tex_width,
        &ctx->texture.tex_door[3].tex_height);
    ctx->texture.tex_door[4].img = mlx_xpm_file_to_image(ctx->mlx,
        "./texture/doors/door_4.xpm", &ctx->texture.tex_door[4].tex_width,
        &ctx->texture.tex_door[4].tex_height);
    init_door_addr(ctx);
}