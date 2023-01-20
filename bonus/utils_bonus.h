/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:44:36 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 14:53:02 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "structs_bonus.h"

void	error_exit(char *msg);
int		get_time(void);
int		get_cur_time(t_ctx *ctx);
void	print_background_minimap(t_ctx *ctx, int scale);
void	init_screen_buffer(t_ctx *ctx);

#endif