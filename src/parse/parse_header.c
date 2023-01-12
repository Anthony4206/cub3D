/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:10:26 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/09 10:34:44 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

#include "../structs.h"
#include "../utils.h"
#include "parse.h"

int	check_int_color(char *str)
{
	int	i;
	int	n;

	i = 0;
	if (str[0] == '-')
		error_exit("Error\nInvalid RGB code\n");
	while (str[0] == '0' && ft_isdigit(str[1]))
		str++;
	while (ft_isdigit(str[i]))
		i++;
	if (i > 3)
		error_exit("Error\nInvalid RGB code\n");
	n = ft_atoi(str);
	if (n > 255)
		error_exit("Error\nInvalid RGB code\n");
	return (n);
}

int	check_colors(char *color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = -1;
	r = check_int_color(color);
	while (ft_isdigit(color[++i]))
		;
	if (!(color[i] == ',' && ft_isdigit(color[i + 1])))
		error_exit("Error\nInvalid color code\n");
	i++;
	g = check_int_color(color + i)
		;
	while (ft_isdigit(color[++i]))
		;
	if (!(color[i] == ',' && ft_isdigit(color[i + 1])))
		error_exit("Error\nInvalid color code\n");
	i++;
	b = check_int_color(color + i);
	while (ft_isdigit(color[++i]))
		;
	return (create_rgb(r, g, b));
}

void	init_texture(char *texture, t_parse *parse, int size, int n)
{
	if (texture[0] == 'N')
		parse->N = add_arg(texture + n, size);
	else if (texture[0] == 'S')
		parse->S = add_arg(texture + n, size);
	else if (texture[0] == 'E')
		parse->E = add_arg(texture + n, size);
	else if (texture[0] == 'W')
		parse->W = add_arg(texture + n, size);
	else if (texture[0] == 'F')
	{
		parse->F = add_arg(texture + n, size);
		parse->F_RGB = check_colors(parse->F);
	}
	else if (texture[0] == 'C')
	{
		parse->C = add_arg(texture + n, size);
		parse->C_RGB = check_colors(parse->C);
	}
}

void	parse_texture(char *texture, t_parse *parse, int size, int n)
{
	if (texture[0] == 'N' && parse->N)
		error_exit("Error\ncified more than once\n");
	else if (texture[0] == 'S' && parse->S)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'W' && parse->W)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'E' && parse->E)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'F' && parse->F)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'C' && parse->C)
		error_exit("Error\nTexture specified more than once\n");
	init_texture(texture, parse, size, n);
}

void	parse_header(t_parse *parse, char **line, int fd)
{
	while (1)
	{
		*line = get_next_line(fd);
		if (!(*line))
        {
	        free(*line);
			error_exit("Error\nInvalid map format\n");
        }
		check_line(parse, *line);
		if (parse->C && parse->E && parse->F && parse->N
			&& parse->S && parse->W)
			break ;
		free(*line);
	}
    check_open_file(parse);
	free(*line);
}
