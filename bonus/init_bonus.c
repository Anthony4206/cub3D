/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:31:42 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/29 16:00:13 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void    clean_buffer()
{
    int y = -1;

    while (++y < height)
    {
        int x = -1;
        while (++x < weight) 
            buffer[y][x] = 0;
    }
}

void	init_camera()
{
	cameraX = 2 * x / (double)w - 1;
	ray_dirX = dirX + planeX * cameraX;
	ray_dirY = dirY + planeY * cameraX;
}

void	init_player()
{
	posX = see map;
	posY = see map;
	dirX = -1; // example
	dirY = 0; // example
	planeX = 0;
	planeY = 0.66;
	time = 0;
	old_time = 0;
}

void	init_ray()
{
	mapX = (int)posX;
	mapY = (int)posY;
	if (ray_dirX == 0)
		delta_distX = 1e30;
	else
		delta_distX = abs(1 / ray_dirX);
	if (ray_dirY == 0)
		delta_distY = 1e30;
	else
		delta_distY = abs(1 / ray_dirY);
	hit = 0;
}

void	init_side_dist()
{
	if (ray_dirX < 0)
	{
		stepX = -1;
		side_distX = (posX - mapX) * delta_distX;
	}
	else
	{
		stepX = 1;
		side_distX = (mapX + 1.0 - posX) * delta_distX;
	}
	if (ray_dirY < 0)
	{
		stepY = -1;
		side_distY = (posY - mapY) * delta_distY;	
	}
	else
	{
		stepY = 1;
		side_distY = (mapY + 1.0 - posY) * delta_distY;
	}
}

void    init_door_img()
{
    //initialiser image
}

void    init_sprite_img()
{
    //initialiser image
}

t_ctx	init_cub(argv[1])
{
	t_ctx	ret;

	/*****
	 * initialiser mlx
	 * initialiser win
	 * initialiser img
	 * initialiser addr
	 * initialiser texture
	 * initialiser addr texture
     * initialiser bonus;
	*****/
	return (ret);
}
