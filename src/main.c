/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:25:14 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/05 15:30:22 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "utils.h"
#include "structs.h"
#include "parse/parse.h"

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc != 2)
		error_exit("error: too few arguments\n");
	ctx.parse = parse(argv[1]);
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
}