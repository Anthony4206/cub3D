/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:59:37 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 14:59:10 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>

#include "../utils_bonus.h"
#include "../structs_bonus.h"
#include "parse_bonus.h"

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
