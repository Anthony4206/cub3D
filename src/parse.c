/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:14:29 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/29 10:20:47 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	parse(char *str)
{
	//vérification de la terminaison du fichier argument (*.cub$)
	//ouverture du fichier
	//lecture du fichier

	//si erreur:
		//print un message d'erreur approprié
		//fermeture du fichier
		//return (-1);
	/*IMPORTANT*/
	/****
	 * on élimine les lignes vides entre les types d'élément
	 * les lignes vides dans la description de la map sont des erreurs
	 * les informations de chaque élément peuvent être séparées par un ou plusieurs espace
	 * La map doit être fermée/entourée de murs (1)
	 * La description de la map accepte les espaces (s'ils sont utilisés intelligement)
	 * les espaces ne doivent pas être éliminés lorsque on parse la map
	 * La map ne doit pas utiliser de caractères interdits (sont autorisés: "01NSEW")
	 * Il ne doit y avoir qu'une seule position de départ (soit: N, S, E ou W)
	****/

	//fermeture du fichier
	//return 0 si pas d'erreur.
}