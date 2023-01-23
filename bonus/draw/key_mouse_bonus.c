/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:18:53 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 15:21:30 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../structs_bonus.h"
#include "draw_bonus.h"

int	press_mouse(int button, int x, int y, void *param)
{
	t_ctx	*ctx;

	(void)x;
	(void)y;
	ctx = (t_ctx *)param;
	if (button == 1)
		ctx->mouse.mouse_pressed = 1;
	return (0);
}

int	release_mouse(int button, int x, int y, void *param)
{
	t_ctx	*ctx;

	(void)x;
	(void)y;
	(void)button;
	ctx = (t_ctx *)param;
	ctx->mouse.mouse_pressed = 0;
	return (0);
}

void	rotate(t_ctx *ctx, float a, int x)
{
	double	tmp_x;
	double	tmp_plane_x;

	tmp_x = ctx->player.dir_x * cos(a) + ctx->player.dir_y * (-sin(a));
	ctx->player.dir_y = ctx->player.dir_x * sin(a)
		+ ctx->player.dir_y * (cos(a));
	ctx->player.dir_x = tmp_x;
	tmp_plane_x = ctx->ray.plane_x * cos(a) - ctx->ray.plane_y * sin(a);
	ctx->ray.plane_y = ctx->ray.plane_x * sin(a) + ctx->ray.plane_y * cos(a);
	ctx->ray.plane_x = tmp_plane_x;
	ctx->mouse.save_x = x;
}

int	move_mouse(int x, int y, void *param)
{
	t_ctx	*ctx;

	(void)y;
	ctx = (t_ctx *)param;
	if (ctx->mouse.mouse_pressed && x < ctx->mouse.save_x)
		rotate(ctx, -0.06, x);
	else if (ctx->mouse.mouse_pressed && x > ctx->mouse.save_x)
		rotate(ctx, 0.06, x);
	return (0);
}
