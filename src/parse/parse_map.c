/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:53:57 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/10 10:56:45 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <stdio.h>

#include "parse.h"
#include "../utils.h"
#include "../structs.h"

void	add_size(t_parse *parse, char **line, int fd)
{
	int		size;

	while (1)
	{
		if (!check_empty_line(*line))
			break ;
		parse->map_height++;
		size = ft_strlen(*line);
		if ((*line)[size - 1] == '\n')
			size--;
		if (size > parse->map_width)
			parse->map_width = size;
		check_map_line(*line);
		free(*line);
		*line = get_next_line(fd);
	}
}

void	get_size_map(t_parse *parse, char *line, int fd)
{
	int		i;

	parse->map_height = 0;
	parse->map_width = 0;
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			error_exit("Error\nNo map\n");
		if (check_empty_line(line))
			break ;
		free(line);
		i++;
	}
	add_size(parse, &line, fd);
	check_if_map_in_last(&line, fd);
	close(fd);
}

char	*useless_line(char **line, int fd)
{
	int	j;

	j = 6;
	while (1)
	{
		*line = get_next_line(fd);
		if (check_empty_line(*line))
			j--;
		free(*line);
		if (j == 0)
			break ;
	}
	*line = get_next_line(fd);
	return (*line);
}

void	init_map_tab(t_parse *parse, char *line, int fd)
{
	int	i;
	int	j;

	i = -1;
	while (++i < parse->map_height)
	{
		if (ft_strchr(line, '\n'))
			ft_strncat(parse->map[i], line, ft_strlen(line) - 1);
		else
			ft_strlcat(parse->map[i], line, -1);
		j = ft_strlen(parse->map[i]) - 1;
		while (++j < parse->map_width)
			parse->map[i][j] = ' ';
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

/*void	display_map(t_parse *parse)
{
	int x;
	int y;

	x = 0;
	y = 0;
//	printf("MAP HEIGHT = %d\n", parse->map_height);
//	printf("MAP WIDTH = %d\n", parse->map_width);
	while (y < parse->map_height)
	{
		while (parse->map[y][x])
//			printf("%c", parse->map[y][x]);
		//printf("Fin de ligne a : %d\n", x);
//		printf("\n");
		x = 0;
		y++;
	}
}*/

void	get_map(t_parse *parse, char *line, int fd, char *file)
{
	int		i;

	i = -1;
	get_size_map(parse, line, fd);
	fd = open(file, O_RDONLY);
	parse->map = ft_calloc(sizeof(char *), parse->map_height + 1);
	while (++i < parse->map_height)
		parse->map[i] = ft_calloc(sizeof(char), parse->map_width + 1);
	useless_line(&line, fd);
	while (!check_empty_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	init_map_tab(parse, line, fd);
//	display_map(parse);
}
