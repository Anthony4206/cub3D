/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:18:21 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 14:57:11 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../utils_bonus.h"

void	check_map_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_strchr("NSEW01 \nDA", line[i]))
		{
			free(line);
			error_exit("Error\nInvalid map format\n");
		}
	}
}

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void	check_if_map_in_last(char **line, int fd)
{
	if (!check_empty_line(*line))
	{
		while (1)
		{
			free(*line);
			*line = get_next_line(fd);
			if (check_empty_line(*line))
			{
				free(*line);
				error_exit("Error\nMap not finishing item\n");
			}
			if (!(*line))
				break ;
		}
	}
	free(*line);
}

void	init_map_door(t_parse *parse)
{
	int	i;

	i = -1;
	parse->map_door = ft_calloc(sizeof(int *), parse->map_height);
	while (++i < parse->map_height)
		parse->map_door[i] = ft_calloc(sizeof(int), parse->map_width);
}
