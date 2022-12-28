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

void	exec_dda()
{
	while (hit == 0)
	{
		if (side_distX < side_distY)
		{
			side_distX += delta_distX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			side_distY += delta_distY;
			mapY += stepY;
			side = 1;			
		}
		if (worldmap[mapX][mapY] > 0)
			hit = 1;
	}
}

void	calc_perp_wall_dist()
{
	if (side ==0)
		perp_wall_dist = (side_distX - delta_distX);
	else
		perp_wall_dist = (side_distY - delta_distY);
}

void	calc_height_wall()
{
	line_height = (int)(h / perp_wall_dist);
	draw_start = -line_height / 2 + h / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + h / 2;
	if (draw_end >= h)
		draw_end = h - 1;
}

void	define_color()
{
	colorRGB	color;

	if (worldmap[mapX][mapY] == 1)
		color = RGB_red;
	else if (worldmap[mapX][mapY] == 2)
		color = RGB_green;
	else if (worldmap[mapX][mapY] == 3)
		color = RGB_blue;
	else if (worldmap[mapX][mapY] == 4)
		color = RGB_white;
	else
		color = RGB_yellow;
	if (side == 1)
		color = color / 2;
	verLine(x, draw_start, draw_end, color);
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