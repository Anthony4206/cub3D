void    init_sprite()
{
    //on parse la map pour lister les sprites et renseigner leurs données
    //on initialise les structs t_sprite
    int     num_sprites = //récupérer le nb de sprite dans le tableau
    Uint32  buffer[screen_height][screen_width];
    double  z_buffer[screen_width];
    int     sprite_tab[num_sprites];
    double  sprite_distance[num_sprites];
    //fonction pour trier les sprites par ordre d'éloignement
    //fonction pour initialiser les textures
    z_buffer[x] = perp_wall_dist;
}

void    draw_sprite()
{
    int i = -1;
    while (++i < num_sprites)
    {
        sprite_order[i] = i;
        sprite_distance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y));
    }
    //fonction pour trier les sprite du plus éloigné au plus proche
    i = 0;
    while (++i < num_sprites)
    {
        double  spriteX = sprite[sprite_order[i]].x - posX;
        double  spriteY = sprite[sprite_order[i]].y - posY;
        double  inv_det = 1.0 / (planeX * dirY - dirX * planeY);
        double  transformX = inv_det * (dirY * spriteX - dirX * spriteY);
        double  transformY = inv_det * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
        int     spriteScreenX = (int)((weight / 2) * (1 + transformX / transformY));
        int     sprite_height = abs((int)(height / transformY)); //using 'transformY' instead of the real distance prevents fisheye
        int     draw_startY = -sprite_height / 2 + height / 2;
        if(draw_startY < 0)
            draw_startY = 0;
        int draw_endY = sprite_height / 2 + height / 2;
        if(draw_endY >= height)
            draw_endY = height - 1;
        int sprite_width = abs( int (height / (transformY)));
        int draw_startX = -sprite_width / 2 + sprite_screenX;
        if(draw_startX < 0)
            draw_startX = 0;
        int draw_endX = sprite_width / 2 + sprite_screenX;
        if(draw_endX >= weight)
            draw_endX = weight - 1;
        int stripe = draw_startX;
        while (++stripe < draw_endX)
        {
            int texX = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screenX)) * tex_width / sprite_width) / 256;
            if (transformY > 0 && stripe > 0 && stripe < weight && transformY < z_buffer[stripe])
            {
                int y = draw_startY    
                while (++y < draw_endY)
                {
                    int d = (y) * 256 - height * 128 + sprite_height * 128;
                    int texY = ((d * tex_height) / sprite_height) / 256;
                    Uint32 color = texture[sprite[sprite_order[i]].texture][tex_width * texY + texX];
                    if((color & 0x00FFFFFF) != 0)
                        buffer[y][stripe] = color;
                }
            }
        }
    }
}