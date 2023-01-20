/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:28:08 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/20 13:28:10 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <math.h>
#include "../structs.h"
#include "walls.h"

int	release_key(int key, void *param)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)param;
	if (key == 13)
		ctx->keys.key_w = false;
	else if (key == 0)
		ctx->keys.key_a = false;
	else if (key == 1)
		ctx->keys.key_s = false;
	else if (key == 2)
		ctx->keys.key_d = false;
	else if (key == 123)
		ctx->keys.key_left = false;
	else if (key == 124)
		ctx->keys.key_right = false;
	return (0);
}

int	press_key(int key, void *param)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)param;
	if (key == 53)
	{
		mlx_destroy_window(ctx->mlx, ctx->win);
		exit(EXIT_SUCCESS);
	}
	else if (key == 13)
		ctx->keys.key_w = true;
	else if (key == 0)
		ctx->keys.key_a = true;
	else if (key == 1)
		ctx->keys.key_s = true;
	else if (key == 2)
		ctx->keys.key_d = true;
	else if (key == 123)
		ctx->keys.key_left = true;
	else if (key == 124)
		ctx->keys.key_right = true;
	return (0);
}
