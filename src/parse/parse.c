/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:59:37 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/05 15:01:18 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <stdio.h>

#include "../utils.h"
#include "../structs.h"
#include "parse.h"

/*void	parse_color()
{
	//parse des textures
	//parse de la couleur du sol
	//parse de la couleur du plafond
}*/

void	parse_header(t_parse *parse, char **line, int fd)
{
	while (1)
	{
		*line = get_next_line(fd);
		if (!(*line))
			error_exit("Error\nInvalid map format\n");
		check_line(parse, *line);
		if (parse->C && parse->E && parse->F && parse->N
			&& parse->S && parse->W)
			break ;
		free(*line);
	}
	free(*line);
}

//les dossiers sont open (à voir)
t_parse	parse(char *str)
{
	t_parse	ret;
	int		fd;
	char	*line;

	ft_bzero(&ret, sizeof(t_parse));
	fd = open(str, O_RDONLY);
	if (fd == -1)
		error_exit("Error\nInvalid map name\n");
	if (ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4))
		error_exit("Error\nInvalid map format\n");
	parse_header(&ret, &line, fd);
	get_map(&ret, line, fd, str);
	parse_wall(ret);
	close(fd);
	return (ret);
}
