/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:25:42 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/09 10:14:09 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALLS_BONUS_H
# define WALLS_BONUS_H

# include "../structs_bonus.h"

int 	draw(t_ctx *ctx);
int		take_instructions_and_draw(t_ctx *ctx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	raycasting_walls(t_ctx *ctx);
void	calculate_side_dist(t_ctx *ctx);
void	exec_dda(t_ctx *ctx, int x);
void	calc_perp_wall_dist(t_ctx *ctx);
void    draw_wall(t_ctx *ctx, int x);
void	color_x_stripe(t_ctx *ctx, int x);
void	calc_x_coord_tex(t_ctx *ctx);
void	calc_wall_x(t_ctx *ctx);
void	calc_height_wall(t_ctx *ctx);
void	draw_and_clear_buffer(t_ctx *ctx);
void	display_buffer(t_ctx *ctx);
int	    ft_close(t_ctx *ctx);
int		press_key(int key, void *param);
int		release_key(int key, void *param);
int	    press_mouse(int button, int x, int y, void *param);
int	    release_mouse(int button, int x, int y, void *param);
int	    move_mouse(int x, int y, void *param);
void	player_moves(t_ctx *ctx);
void	player_rotates(t_ctx *ctx);
void    draw_sprite(t_ctx *ctx);
void	sort_sprites(t_ctx *ctx);
void	calc_order_sprite_dist(t_ctx *ctx);
void	transform_sprite_coord(t_ctx *ctx, int i);
void	raycasting_doors(t_ctx *ctx);

#endif