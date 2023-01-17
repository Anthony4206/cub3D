/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:27:58 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/16 07:22:44 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_BONUS_H
# define INIT_BONUS_H

# include <math.h>
# include <stdbool.h>

# include "structs_bonus.h"

void	init_cub(t_ctx *ctx);
void    init_mini_map(t_ctx *ctx);
void    draw_minimap(t_ctx *ctx);
void    init_sprite(t_ctx *ctx);

#endif
