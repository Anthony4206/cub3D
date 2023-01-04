#include "libft.h"
#include "utils.h"
#include "structs.h"
#include "parse.h"

//cameraX: points to the right vertical stripe, x-coordinate on the camera plane
//with cameraX=0 being the center, camX=-1 being left side, camX=1 being right side
//x is the x-coord on the screen (ex:50 is at the center of a 100-wide screen)
//w is the width of the screen
//PAS A INITIALISER: CALCULATION for each ray dir_vector coordinates
void	calculate_rays(t_ctx *ctx)
{
	int	x;
	
	x = 0;
	ctx->ray.mapX = ctx->player.posX;
	ctx->ray.mapY = ctx->player.posY;
	while (x++ < ctx->img.width)
	{
		ctx->ray.cameraX = 2 * x / (double)ctx->img.width - 1;
		ctx->ray.ray_dirX = ctx->player.dirX + ctx->ray.plane_X * ctx->ray.cameraX;
		ctx->ray.ray_dirY = ctx->player.dirY + ctx->ray.plane_Y * ctx->ray.cameraX;
		if (ctx->ray.ray_dirX == 0)
			ctx->ray.delta_distX = 1e30;
		else
			ctx->ray.delta_distX = abs(1 / ctx->ray.ray_dirX);
		if (ctx->ray.ray_dirY == 0)
			ctx->ray.delta_distY = 1e30;
		else
			ctx->ray.delta_distY = abs(1 / ctx->ray.ray_dirY);
		calculate_side_dist(ctx);
		exec_dda(ctx);
		calc_perp_wall_dist(ctx);
	}
}

//stepX and StepY eather -1 or +1 to indicate the dir of the ray
void	calculate_side_dist(t_ctx *ctx)
{
	if (ctx->ray.ray_dirX < 0)
	{
		ctx->ray.stepX = -1;
		ctx->ray.side_distX = (posX - mapX) * ctx->ray.delta_distX;
	}
	else
	{
		ctx->ray.stepX = 1;
		ctx->ray.side_distX = (mapX + 1.0 - posX) * ctx->ray.delta_distX;
	}
	if (ctx->ray.ray_dirY < 0)
	{
		ctx->ray.stepY = -1;
		ctx->ray.side_distY = (posY - mapY) * ctx->ray.delta_distY;	
	}
	else
	{
		ctx->ray.stepY = 1;
		ctx->ray.side_distY = (mapY + 1.0 - posY) * ctx->ray.delta_distY;
	}
}
//if side == 1, we bumped a Yline => N or S wall
// if side == 0, a x-line => E or W wall
//we check if the square we bumped into belongs to a wall, if yes, we stop
void	exec_dda(t_ctx *ctx)
{
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (ctx->ray.side_distX < ctx->ray.side_distY)
		{
			ctx->ray.side_distX += ctx->ray.delta_distX;
			ctx->ray.mapX += ctx->ray.stepX;
			ctx->ray.hit_side = 0;
		}
		else
		{
			ctx->ray.side_distY += ctx->ray.delta_distY;
			ctx->ray.mapY += ctx->ray.stepY;
			ctx->ray.hit_side = 1;			
		}
		if (worldmap[ctx->ray.mapX][ctx->ray.mapY] > 0)
			hit = true;
	}
}

void	calc_perp_wall_dist(t_ctx *ctx)
{
	if (ctx->ray.hit_side == 0)
		ctx->ray.perp_wall_dist = (ctx->ray.side_distX - ctx->ray.delta_distX);
	else
		ctx->ray.perp_wall_dist = (ctx->ray.side_distY - ctx->ray.delta_distY);
}