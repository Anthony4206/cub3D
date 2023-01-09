void    draw_background()
{
    int x;
    int y;
    //init background
    /*POUR LE SOL*/
    y = -1;
    while (++y < height)
    {
        ray_dirX0 = dirX - planeX;
        ray_dirY0 = dirY - planeY;
        ray_dirX1 = dirX + planeX;
        ray_dirY1 = dirY + planeY;
        pos = y - screen_height / 2;
        posZ = 0.5 * screen_height;
        row_distance = posZ / pos;
        floorStepX = row_distance * (ray_dirX1 - ray_dirX0) / screenWidth;
        floorStepY = row_distance * (ray_dirY1 - ray_dirY0) / screenWidth;
        floorX = posX + row_distance * ray_dirX0;
        floorY = posY + row_distance * ray_dirY0;
        x = -1;
        while (++x < width)
        {
            cellX = (int)floorX;
            cellY = (int)floorY;
            tx = (int)(tex_width * (floorX - cellX)) & (tex_width - 1);
            ty = (int)(tex_height * (floorY - cellY)) & (tex_height - 1);
            floorX += floor_stepX;
            floorY += floor_stepY;
            floor_tex = 3;
            cell_tex = 6;
            color = texture[floor_tex][tex_width * ty + tx];
            color = (color >> 1) & 8355711; // make a bit darker
            buffer[y][x] = color;
            color = texture[cell_tex][tex_width * ty + tx];
            color = (color >> 1) & 8355711; // make a bit darker
            buffer[screen_height - y - 1][x] = color;
        }
    }
}

void    draw()
{
    //prise en compte d'un eventuel déplacement
    //On dessine l'arrière plan (sol et plafond)
    //On dessine les mur
    //mlx_put_img
}