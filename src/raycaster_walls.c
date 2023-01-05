#include "libft.h"
#include "utils.h"
#include "structs.h"
#include "parse.h"

void	generate_texture(t_ctx *ctx)
{
	for(int x = 0; x < ctx->tex.tex_width; x++)
  for(int y = 0; y < ctx->tex.tex_height; y++)
  {
    int xorcolor = (x * 256 / ctx->tex.tex_width) ^ (y * 256 / ctx->tex.tex_height);
    //int xcolor = x * 256 / texWidth;
    int ycolor = y * 256 / ctx->tex.tex_height;
    int xycolor = y * 128 / ctx->tex.tex_height + x * 128 / ctx->tex.tex_width;
    ctx->tex.texture[0][ctx->tex.tex_width * y + x] = 65536 * 254 * (x != y && x != ctx->tex.tex_width - y); //flat red texture with black cross
	ctx->tex.texture[1][ctx->tex.tex_width * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
	ctx->tex.texture[2][ctx->tex.tex_width * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
	ctx->tex.texture[3][ctx->tex.tex_width * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
	ctx->tex.texture[4][ctx->tex.tex_width * y + x] = 256 * xorcolor; //xor green
	ctx->tex.texture[5][ctx->tex.tex_width * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
	ctx->tex.texture[6][ctx->tex.tex_width * y + x] = 65536 * ycolor; //red gradient
	ctx->tex.texture[7][ctx->tex.tex_width * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
  }
}

//cameraX: points to the right vertical stripe, x-coordinate on the camera plane
//with cameraX=0 being the center, camX=-1 being left side, camX=1 being right side
//x is the x-coord on the screen (ex:50 is at the center of a 100-wide screen)
//w is the width of the screen
//PAS A INITIALISER: CALCULATION for each ray dir_vector coordinates
void	calculate_rays(t_ctx *ctx)
{
	int	x;
	
	x = 0;
	//ctx->time.time = 0;
	//ctx->time.old_time = 0;
	generate_texture(ctx);
	ctx->ray.mapX = (int)ctx->player.posX;
	ctx->ray.mapY = (int)ctx->player.posY;
	while (x++ < ctx->screen.width)
	{
		ctx->ray.cameraX = 2 * x / (double)ctx->screen.width - 1;
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
		draw_wall(ctx, x);
	}
}

//stepX and StepY eather -1 or +1 to indicate the dir of the ray
void	calculate_side_dist(t_ctx *ctx)
{
	if (ctx->ray.ray_dirX < 0)
	{
		ctx->ray.stepX = -1;
		ctx->ray.side_distX = (ctx->player.posX - ctx->ray.mapX) * ctx->ray.delta_distX;
	}
	else
	{
		ctx->ray.stepX = 1;
		ctx->ray.side_distX = (ctx->ray.mapX + 1.0 - ctx->player.posX) * ctx->ray.delta_distX;
	}
	if (ctx->ray.ray_dirY < 0)
	{
		ctx->ray.stepY = -1;
		ctx->ray.side_distY = (ctx->player.posY - ctx->ray.mapY) * ctx->ray.delta_distY;	
	}
	else
	{
		ctx->ray.stepY = 1;
		ctx->ray.side_distY = (ctx->ray.mapY + 1.0 - ctx->player.posY) * ctx->ray.delta_distY;
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