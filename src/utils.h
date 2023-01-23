/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:58:20 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/23 12:19:31 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

void	error_exit(char *msg);
int		create_rgb(int r, int g, int b);
int		ft_close(t_ctx *ctx);

#endif
