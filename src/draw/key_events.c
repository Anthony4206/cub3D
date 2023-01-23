/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:28:08 by mdemma            #+#    #+#             */
/*   Updated: 2023/01/23 15:57:35 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <math.h>
#include "../structs.h"
#include "draw.h"

int	release_key(int key, void *param)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)param;
	if (key == 13)
		ctx->keys.key_w = false;
	if (key == 0)
		ctx->keys.key_a = false;
	if (key == 1)
		ctx->keys.key_s = false;
	if (key == 2)
		ctx->keys.key_d = false;
	if (key == 123)
		ctx->keys.key_left = false;
	if (key == 124)
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
	if (key == 13)
		ctx->keys.key_w = true;
	if (key == 0)
		ctx->keys.key_a = true;
	if (key == 1)
		ctx->keys.key_s = true;
	if (key == 2)
		ctx->keys.key_d = true;
	if (key == 123)
		ctx->keys.key_left = true;
	if (key == 124)
		ctx->keys.key_right = true;
	return (0);
}
