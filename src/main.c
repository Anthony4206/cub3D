/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:25:14 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/10 10:55:05 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "utils.h"
#include "init.h"
#include "structs.h"
#include "parse/parse.h"
#include "draw/draw.h"

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc != 2)
		error_exit("error: too few arguments\n");
	ft_bzero(&ctx, sizeof(t_ctx));
	ctx.parse = parse(argv[1]);
	init_cub(&ctx);
	printf("HEIGHT = %d, WIDTH = %d, mapXY = %c\n", ctx.parse.map_height, ctx.parse.map_width, ctx.parse.map[0][32]);
	take_instructions_and_draw(&ctx);
	mlx_loop(ctx.mlx);
	return (0);
}
