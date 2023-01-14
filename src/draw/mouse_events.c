#include <libft.h>
#include "../structs.h"
#include "walls.h"

//  mouse_hook(int button,int x,int y,void *param); mlx mandatory
//zooms in and out when scrolling, notify when mouse left button pressed
// int	press_mouse(int button, int x, int y, void *param) 
// {
// 	t_global	*global;

// 	(void)x;
// 	(void)y;
// 	global = (t_global *)param;
// 	if (button == 4 || button == 5)
// 		zoom(button, global);
// 	if (button == 1)
// 		global->mouse_pressed = 1;
// 	return (0);
// }

// //notify when mouse left button is released
// int	release_mouse(int button, int x, int y, void *param)
// {
// 	t_global	*global;

// 	(void)x;
// 	(void)y;
// 	(void)button;
// 	global = (t_global *)param;
// 	global->mouse_pressed = 0;
// 	return (0);
// }

// // records mouse movements for rotation
// int	move_mouse(int x, int y, void *param)
// {
// 	t_global	*global;

// 	global = (t_global *)param;
// 	global->cam->previous_x = global->cam->x;
// 	global->cam->previous_y = global->cam->y;
// 	global->cam->x = x;
// 	global->cam->y = y;
// 	if (global->mouse_pressed)
// 	{
// 		global->cam->y_rotation += (x - global->cam->previous_x) * 0.001;
// 		global->cam->x_rotation += (y - global->cam->previous_y)* 0.001;
// 		ft_bzero(global->img->addr, global->img->img_height * global->img->line_length);
// 		create_grid(global->all_coord_parsing, global->img, *(global->map), global);
// 	}
// 	return (0);
// }

//press x will close window and end program
int	close_win_mouse(void *param)
{
	t_ctx	*ctx;
	
	ctx = (t_ctx *)param;
	end_program(ctx);
	exit(EXIT_SUCCESS);
	return (0);
}