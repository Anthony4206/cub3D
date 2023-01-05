/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:18:21 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/05 15:52:32 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../utils.h"

void	check_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("NSEW01 \n", line[i]))
		{
			free(line);
			error_exit("Error\nInvalid map format\n");
		}
		i++;
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

void	check_if_map_in_last(char *line, int fd)
{
	if (!check_empty_line(line))
	{
		while (1)
		{
			free(line);
			line = get_next_line(fd);
			if (check_empty_line(line) || !line)
				break ;
		}
		if (check_empty_line(line))
			error_exit("Error\nMap not finishing item\n");
	}
//	free(line);
}
