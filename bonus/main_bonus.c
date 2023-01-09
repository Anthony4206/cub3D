/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:25:14 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/29 13:25:34 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc != 2)
	{
		//message d'erreur
		//exit failure
	}
	if (parse_error(/*argv[1]*/"maps/42.cub"))
	{
		//message d'erreur (envoyé directement dans la fonction parse)
		//exit failure
	}
	ctx = parse(/*argv[1]*/"maps/42.cub");
    // parse_error et parse peuvent aussi être fait ensemble
    init_cub(&ctx);
    init_sprite(&ctx);
    //mlx_hook pour configurer les touches d'action
    //initialiser aussi la key pour les portes.
    //mlx_hook pour configurer le bonus souris
	//mlx_look qui renvoi à la fonction pour dessiner
    //return
}