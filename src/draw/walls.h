/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:25:42 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/05 17:25:44 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALLS_H
# define WALLS_H

# include "../structs.h"

void	raycasting_walls(t_ctx *ctx);
void	calculate_side_dist(t_ctx *ctx);
void	exec_dda(t_ctx *ctx);
void	calc_perp_wall_dist(t_ctx *ctx);
void    draw_wall(t_ctx *ctx, int x);
void	color_x_stripe(t_ctx *ctx, int x);
void	calc_x_coord_tex(t_ctx *ctx);
void	calc_wall_x(t_ctx *ctx);
void	calc_height_wall(t_ctx *ctx);

#endif