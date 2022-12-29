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
	if (parse(argv[1]))
	{
		//message d'erreur (envoyé directement dans la fonction parse)
		//exit failure
	}
	ctx = init_cub(argv[1]);
	
}