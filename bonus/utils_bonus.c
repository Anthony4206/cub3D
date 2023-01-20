/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:44:58 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 14:50:33 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "structs_bonus.h"

//tv_sec = seconds, tv.usec = micro seconds;
//gettimeofday: returns time in microseconds
//init_time returns time in milliseconds
int	get_time(void)
{
	struct timeval	cur_time;
	unsigned int	time;

	gettimeofday(&cur_time, NULL);
	time = (cur_time.tv_sec * 1000000) + cur_time.tv_usec;
	return (time);
}

//in milliseconds
int	get_cur_time(t_ctx *ctx)
{
	unsigned int	t;

	t = (get_time() - ctx->time.init_time);
	return (t);
}

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	init_screen_buffer(t_ctx *ctx)
{
	int	y;

	y = -1;
	ctx->screen.buffer = ft_calloc(sizeof(unsigned int *), HEIGHT);
	while (++y < HEIGHT)
		ctx->screen.buffer[y] = ft_calloc(sizeof(unsigned int), WIDTH);
}
