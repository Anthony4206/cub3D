/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:58:14 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/23 12:18:04 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "structs.h"

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	ft_close(t_ctx *ctx)
{
	mlx_destroy_window(ctx->mlx, ctx->win);
	exit (EXIT_SUCCESS);
}
