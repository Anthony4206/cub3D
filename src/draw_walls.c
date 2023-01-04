/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:48:49 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/28 12:57:54 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "structs.h"
#include "parse.h"

void	calc_height_wall(t_ctx *ctx)
{
	line_height = (int)(h / perp_wall_dist);
	draw_start = -line_height / 2 + h / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + h / 2;
	if (draw_end >= h)
		draw_end = h - 1;
}

void    wall()
{
    int     tex_num = worldMap[mapX][mapY] - 1;
    double  wallX;
    if (side == 0)
        wallX = posY + perp_wall_dist * ray_dirY;
    else
        wallX = posX + perp_wall_dist * ray_dirX;
    wallX -= floor((wallX));
    int texX = (int)(wallX * (double)tex_width);
    if (side == 0 && ray_dirX > 0)
        texX = tex_width - texX - 1;
    if (side == 1 && ray_dirY < 0) 
        texX = tex_width - texX - 1;
    double step = 1.0 * tex_height / line_height;
    double tex_pos = (draw_start - h / 2 + line_height / 2) * step;
    int y = draw_start;
    while (++y < draw_end)
    {
        int texY = (int)tex_pos & (tex_height - 1);
        tex_pos += step;
        int color = texture[tex_num][tex_width * texY + texX];
        if (side == 1)
            color = (color >> 1) & 8355711;
        buffer[y][x] = color;
    }
}

void	calc_FPS()
{
	old_time = time;
	temps = getTicks();
	double frame_time = (time - old_time) / 1000.0;
	print(1.0 / frame_time);
	redraw();
	cls();

	//speed modifiers
	double	move_speed = frame_time * 5.0;
	double	rot_speed = frame_time * 3.0;
}