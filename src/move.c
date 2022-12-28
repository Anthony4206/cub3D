/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:37:51 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/28 12:57:53 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	read_keys()
{
	if (key_down(UP))
	{
		if (world_map[(int)(posX + dirX * move_speed)][(int)(posY)] == 0)
			posX += dirX * move_speed;
		if (world_map[(int)(posX)][(int)(posY + dirY * move_speed)] == 0)
			posY += dirY * move_speed;
	}
	if (key_down(DOWN))
	{
		if (world_map[(int)(posX - dirX * move_speed)][(int)(posY)] == 0)
			posX -= dirX * move_speed;
		if (world_map[(int)(posX)][(int)(posY - dirY * move_speed)] == 0)
			posY -= dirY * move_speed;
	}
	if (key_down(RIGHT))
	{
		double	old_dirX = dirX;
		dirX = dirX * cos(-rot_speed) - dirY * sin(-rot_speed);
		dirY = old_dirX * sin(-rot_speed) + dirY * cos(-rot_speed);
		double	old_planeX = planeX;
		planeX = planeX * cos(-rot_speed) - planeY * sin(-rot_speed);
		planeY = old_planeX * sin(-rot_speed) + planeY * cos(-rot_speed);		
	}
	if (key_down(LEFT))
	{
		double	old_dirX = dirX;
		dirX = dirX * cos(rot_speed) - dirY * sin(rot_speed);
		dirY = old_dirX * sin(rot_speed) + dirY * cos(rot_speed);
		double	old_planeX = planeX;
		planeX = planeX * cos(rot_speed) - planeY * sin(rot_speed);
		planeY = old_planeX * sin(rot_speed) + planeY * cos(rot_speed);		
	}
}