#include "libft.h"
#include "../utils_bonus.h"
#include "../init_bonus.h"
#include "../structs_bonus.h"
#include "../parse/parse_bonus.h"
#include "walls_bonus.h"

void    init_sprite(t_ctx *ctx)
{
    //on parse la map pour lister les sprites et renseigner leurs données
    //on initialise les structs t_sprite
    ctx->sprite.num = 1;
    ctx->sprite.z_buffer = malloc(sizeof(double) * WIDTH);
    ctx->sprite.sprite_order = malloc(sizeof(int) * ctx->sprite.num);
    ctx->sprite.sprite_distance = malloc(sizeof(double) * ctx->sprite.num);
    ctx->sprite.sprite = malloc(sizeof(t_coord) * ctx->sprite.num);
    //fonction pour trier les sprites par ordre d'éloignement
    //fonction pour initialiser les textures
}

int    is_sorted(t_sprite sprite)
{
    int i;

    i = -1;
    while (++i < sprite.num - 1)
    {
        if (sprite.sprite_distance[i] < sprite.sprite_distance[i + 1])    
            return (0);
    }
    return (1);
}

//fonction pour trier les sprite du plus éloigné au plus proche
void    sort_sprites(t_ctx *ctx)
{
    int     i;
    int     tmp;

    while (!is_sorted(ctx->sprite))
    {  
        i = -1;
        while (++i < ctx->sprite.num - 1)
        {
            ctx->sprite.sprite_order[i] = i;
            if (ctx->sprite.sprite_distance[i] < ctx->sprite.sprite_distance[i + 1])
            {
                tmp = ctx->sprite.sprite_order[i]; 
                ctx->sprite.sprite_order[i] = ctx->sprite.sprite_order[i + 1];
                ctx->sprite.sprite_order[i + 1] = tmp;
            }
        }
    }
}

//sprite[i] => ctx->sprite[i].addr
void    draw_sprite(t_ctx *ctx)
{
    int i;

    i = -1;
    while (++i < ctx->sprite.num)
    {
        ctx->sprite.sprite_order[i] = i;
        ctx->sprite.sprite_distance[i] = ((ctx->player.posX - ctx->sprite.sprite[i].x)
        * (ctx->player.posX - ctx->sprite.sprite[i].x)
        + (ctx->player.posY - ctx->sprite.sprite[i].y) * (ctx->player.posY - ctx->sprite.sprite[i].y));
    }
    sort_sprites(ctx;)
    i = -1;
    while (++i < ctx->sprite.num)
    {
        ctx->sprite.spriteX = ctx->sprite.sprite[ctx->sprite.sprite_order[i]].x - ctx->player.posX;
        ctx->sprite.spriteY = tx->sprite.sprite[tx->sprite.sprite_order[i]].y - ctx->player.posY;
        double  inv_det = 1.0 / (ctx->ray.plane_X * ctx->player.dirY - ctx->player.dirX * ctx->ray.planeY);
        double  transformX = inv_det * (ctx->player.dirY * ctx->sprite.spriteX - ctx->player.dirX * ctx->sprite.spriteY);
        double  transformY = inv_det * (-ctx->ray.planeY * ctx->sprite.spriteX + ctx->ray.planeX * ctx->sprite.spriteY); //this is actually the depth inside the screen, that what Z is in 3D
        int     sprite_screenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
        int     sprite_height = abs((int)(HEIGHT / transformY)); //using 'transformY' instead of the real distance prevents fisheye
        int     draw_startY = -sprite_height / 2 + HEIGHT / 2;
        if(draw_startY < 0)
            draw_startY = 0;
        int draw_endY = sprite_height / 2 + HEIGHT / 2;
        if(draw_endY >= HEIGHT)
            draw_endY = HEIGHT - 1;
        int sprite_width = abs( int (HEIGHT / (transformY)));
        int draw_startX = -sprite_width / 2 + sprite_screenX;
        if(draw_startX < 0)
            draw_startX = 0;
        int draw_endX = sprite_width / 2 + sprite_screenX;
        if(draw_endX >= WIDTH)
            draw_endX = WIDTH - 1;
        int stripe = draw_startX;
        unsigned int color;
        while (++stripe < draw_endX)
        {
            int texX = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screenX)) * ctx->texture.sprite[sprite_order[i]].tex_width / sprite_width) / 256;
            if (transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < ctx->sprite.z_buffer[stripe])
            {
                int y = draw_startY    
                while (++y < draw_endY)
                {
                    int d = (y) * 256 - HEIGHT * 128 + sprite_height * 128;
                    int texY = ((d * ctx->texture.sprite[sprite_order[i]].tex_height) / sprite_height) / 256;
                    color = ctx->texture.sprite[sprite_order[i]].addr[ctx->texture.sprite[sprite_order[i]].tex_width * texY + texX];
                    if((color & 0x00FFFFFF) != 0)
                        buffer[y][stripe] = color;
                }
            }
        }
    }
}