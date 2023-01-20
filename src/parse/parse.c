/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:59:37 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/10 10:57:36 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../utils.h"
#include "../structs.h"
#include "parse.h"

t_parse	parse(char *str)
{
	t_parse	ret;
	int		fd;
	char	*line;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		error_exit("Error\nInvalid map name\n");
	if (ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4))
		error_exit("Error\nInvalid map format\n");
	ft_bzero(&ret, sizeof(t_parse));
	parse_header(&ret, &line, fd);
	get_map(&ret, line, fd, str);
	parse_wall(&ret);
	close(fd);
	return (ret);
}
