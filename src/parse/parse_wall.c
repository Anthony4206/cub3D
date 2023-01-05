/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:05:33 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/05 16:08:54 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

#include "../structs.h"
#include "../utils.h"
#include "parse.h"

void	check_pos_wall(t_parse *parse, int *pos, int *player, int i)
{
	int	j;

	j = -1;
	while (parse->map[i][++j])
	{
		if (ft_strchr("NSEW", parse->map[i][j]))
		{
			(*player)++;
			if (*player == 1)
				parse_player(parse, &parse->map[i][j], i, j);
		}
		if (ft_strchr("0NSEW", parse->map[i][j]) && j > *pos)
			*pos = j;
	}
}

int	chr_last_wall(t_parse *parse, char **map)
{
	int	i;
	int	player;
	int	ret;

	i = -1;
	ret = 0;
	player = 0;
	while (map[++i])
		check_pos_wall(parse, &ret, &player, i);
	if (player != 1)
		error_exit("Error\nInvalid number of players\n");
	return (ret + 1);
}

void	check_is_close(t_parse parse, int last, int i, int j)
{
	if (i == 0 || i == parse.map_height - 1)
	{
		if (!ft_strchr(" 1", parse.map[i][j]))
			error_exit("Error\nMap is not close\n");
	}
	else
	{
		if (!ft_strchr(" 1", parse.map[i][0])
			|| !ft_strchr(" 1", parse.map[i][last]))
			error_exit("Error\nMap is not close\n");
		if (ft_strchr("NSEW0", parse.map[i][j]))
			check_pos(parse.map, i, j);
	}
}

void	parse_wall(t_parse parse)
{
	int	i;
	int	j;
	int	last;

	last = chr_last_wall(&parse, parse.map);
	i = -1;
	while (++i < parse.map_height)
	{
		j = -1;
		while (parse.map[i][++j] && j <= last)
			check_is_close(parse, last, i, j);
	}
}
