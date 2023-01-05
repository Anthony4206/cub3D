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

#include "../utils.h"
#include "../structs.h"
#include "parse.h"

/*void	parse_color()
{
    //parse des textures
    //parse de la couleur du sol
    //parse de la couleur du plafond
}*/

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
		error_exit("Error\nInvalid map format 1\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		check_line(&ret, line);
		if (ret.C && ret.E && ret.F && ret.N && ret.S && ret.W)
			break ;
		free(line);
	}
	free(line);
	get_map(&ret, fd, str);
	parse_wall(ret);
	return (ret);
}
