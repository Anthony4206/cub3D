/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:35:02 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/05 15:42:04 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../structs.h"
#include "../utils.h"
#include "parse.h"


void	check_pos(char **map, int i, int j)
{
	if (map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' '
		|| map[i - 1][j + 1] == ' ' || map[i][j - 1] == ' '
		|| map[i][j + 1] == ' ' || map[i + 1][j - 1] == ' '
		|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ')
		error_exit("Error\nMap is not close\n");
}

void	parse_player(t_parse *parse, char *orient, int i, int j)
{
	parse->init_posX = j;
	parse->init_posY = i;
	printf("J posX = %f\n", parse->init_posX);
	printf("I posY = %f\n", parse->init_posY);
	parse->init_dir = *orient;
	*orient = '0';
}
