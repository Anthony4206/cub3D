#include <libft.h>

#include "../structs_bonus.h"
#include "walls_bonus.h"

 int	press_mouse(int button, int x, int y, void *param) 
 {
 	t_ctx	*ctx;

 	(void)x;
 	(void)y;
 	ctx = (t_ctx *)param;
 	if (button == 1)
 		ctx->mouse.mouse_pressed = 1;
 	return (0);
 }

int	release_mouse(int button, int x, int y, void *param)
{
    t_ctx	*ctx;

    (void)x;
    (void)y;
    (void)button;
    ctx = (t_ctx *)param;
    ctx->mouse.mouse_pressed = 0;
    return (0);
}

void    rotate(t_ctx *ctx, float a, int x)
{
	double	tmp_x;
	double	tmp_plane_x;
    
    tmp_x = ctx->player.dirX * cos(a) + ctx->player.dirY * (-sin(a));
    ctx->player.dirY = ctx->player.dirX * sin(a) + ctx->player.dirY * (cos(a));
    ctx->player.dirX = tmp_x;
    tmp_plane_x = ctx->ray.plane_X * cos(a) - ctx->ray.plane_Y * sin(a);
    ctx->ray.plane_Y =ctx->ray.plane_X * sin(a) + ctx->ray.plane_Y * cos(a);
    ctx->ray.plane_X = tmp_plane_x;
    ctx->mouse.save_x = x;    
}

int	move_mouse(int x, int y, void *param)
{
    t_ctx   *ctx;

    (void)y;
    ctx = (t_ctx *)param;
    if (ctx->mouse.mouse_pressed && x < ctx->mouse.save_x)
        rotate(ctx, -0.04, x);
    else if (ctx->mouse.mouse_pressed && x > ctx->mouse.save_x)
        rotate(ctx, 0.04, x);
	return (0);
}
