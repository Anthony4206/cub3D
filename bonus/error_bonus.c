int	parse_error(char *str)
{
	//vérification de la terminaison du fichier argument (*.cub$)
    //vérifier qu'un nom valide ne soit pas un dossier
	//ouverture du fichier
	//lecture du fichier

	//si erreur:
		//print un message d'erreur approprié
		//fermeture du fichier
		//return (-1);
	/*IMPORTANT*/
	/****
     * on vérifie le format RGB et on valide les info (6 lignes avec les bons initials)
     * attention aux doublons
     * vérifier les informations qui suivent les initials 
     * liste : bon format après P et C, pas de virgule en trop, over int, chiffre supérieur à 255
     * il ne doit pas y avoir de valeur supérieur ou inférieur à int max ou int min
     * il ne dois pas y avoir de virgule
	 * on élimine les lignes vides entre les types d'élément
	 * les lignes vides dans la description de la map sont des erreurs
     * que la map est bien présente et bien à la fin du fichier
     * 
	 * les informations de chaque élément peuvent être séparées par un ou plusieurs espace
	 * La map doit être fermée/entourée de murs (1)
	 * La description de la map accepte les espaces (s'ils sont utilisés intelligement)
	 * les espaces ne doivent pas être éliminés lorsque on parse la map
	 * La map ne doit pas utiliser de caractères interdits (sont autorisés: "01NSEW")
	 * Il ne doit y avoir qu'une seule position de départ (soit: N, S, E ou W)
     * Il doit forcément y avoir un joueur
    ****/

	//fermeture du fichier
	//return 0 si pas d'erreur.
}


