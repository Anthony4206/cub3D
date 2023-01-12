#include "libft.h"
#include "../utils.h"
#include "../init.h"
#include "../structs.h"
#include "../parse/parse.h"

//A CHANGER AVEC LES TEXTURES IMPORTEES
void	generate_texture(t_ctx *ctx)
{
	ctx->tex.texture = ft_calloc(4, sizeof(int *));
	ctx->tex.texture[0] = ft_calloc(ctx->tex.tex_width * ctx->tex.tex_height + ctx->tex.tex_width, sizeof(int));
	ctx->tex.texture[1] = ft_calloc(ctx->tex.tex_width * ctx->tex.tex_height + ctx->tex.tex_width, sizeof(int));
	ctx->tex.texture[2] = ft_calloc(ctx->tex.tex_width * ctx->tex.tex_height + ctx->tex.tex_width, sizeof(int));
	ctx->tex.texture[3] = ft_calloc(ctx->tex.tex_width * ctx->tex.tex_height + ctx->tex.tex_width, sizeof(int));
	for(int x = 0; x < ctx->tex.tex_width; x++)
	for(int y = 0; y < ctx->tex.tex_height; y++)
{

	ctx->tex.texture[0][ctx->tex.tex_width * y + x] = 0x0000FF; //BLEU = NORD
	ctx->tex.texture[1][ctx->tex.tex_width * y + x] = 0x7dff42;; //vert = EST
	ctx->tex.texture[2][ctx->tex.tex_width * y + x] = 0xfabc3c; //yellow = SUD
	ctx->tex.texture[3][ctx->tex.tex_width * y + x] = 0xc442ff; //purple = OUEST
}
	// int y;
	// int	x;
	// //int	pixel;
	// char	*dst;

	// y = -1;
	// while (++y < ctx->tex.tex_height)
	// {
	// 	x = -1;
	// 	while (++x < ctx->tex.tex_width)
	// 	{
	// 		//printf("TEXTURE MUR ? ctx->texture.N_wall.img = %s\n", ((char *)(ctx->texture.N_wall.img)));
	// 		//pixel = ctx->tex.tex_width * y * 4 + x;
	// 		//dst = ctx->texture.N_wall.img + (y * ctx->tex.tex_width + x);
	// 		dst = ctx->texture.N_wall.img + ((y * ctx->tex.tex_width + x));
	// 		ctx->tex.texture[0][ctx->tex.tex_width * y + x] = create_rgb(*dst, *(dst + 1), *(dst + 2));
	// 		ctx->tex.texture[1][ctx->tex.tex_width * y + x] = 0x7dff42;; //vert = EST
	// 		ctx->tex.texture[2][ctx->tex.tex_width * y + x] = 0xfabc3c; //yellow = SUD
	// 		ctx->tex.texture[3][ctx->tex.tex_width * y + x] = 0xc442ff; //purple = OUEST
	// 	}
	// }
}