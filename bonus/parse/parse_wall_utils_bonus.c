/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:35:02 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 07:39:18 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../structs_bonus.h"
#include "../utils_bonus.h"
#include "parse_bonus.h"


void	check_pos(char **map, int i, int j)
{
	if (map[i - 1][j] == ' ' || map[i][j - 1] == ' '
		|| map[i][j + 1] == ' ' || map[i + 1][j] == ' ')
		error_exit("Error\nMap is not close\n");
}

void	parse_player(t_parse *parse, char *orient, int i, int j)
{
	parse->init_posX = j;
	parse->init_posY = i;
	parse->init_dir = *orient;
	*orient = '0';
}
