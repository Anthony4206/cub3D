/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:25:14 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/09 11:31:08 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "utils.h"
#include "init.h"
#include "structs.h"
#include "parse/parse.h"
#include "draw/walls.h"

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	(void)argv;
	(void)argc;
	/*if (argc != 2)
		error_exit("error: too few arguments\n");*/
    ft_bzero(&ctx, sizeof(t_ctx));
	ctx.parse = parse(/*argv[1]*/"maps/42.cub");
	init_cub(&ctx);
	//raycasting_walls(&ctx);
//	system("leaks cub3D");
	
	{
		//message d'erreur (envoyé directement dans la fonction parse)
		//exit failure
	}
	 // parse_error et parse peuvent aussi être fait ensemble
    //init_cub(&ctx);
    //mlx_hook pour configurer les touches d'action
	//mlx_loop qui renvoi à la fonction pour dessiner
    //return
	return (0);
}