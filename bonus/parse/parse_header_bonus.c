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

#include "../structs_bonus.h"
#include "../utils_bonus.h"
#include "parse_bonus.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

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
		parse->no = add_arg(texture + n, size);
	else if (texture[0] == 'S')
		parse->so = add_arg(texture + n, size);
	else if (texture[0] == 'E')
		parse->ea = add_arg(texture + n, size);
	else if (texture[0] == 'W')
		parse->we = add_arg(texture + n, size);
	else if (texture[0] == 'F')
	{
		parse->floor = add_arg(texture + n, size);
		parse->f_rgb = check_colors(parse->floor);
	}
	else if (texture[0] == 'C')
	{
		parse->ceiling = add_arg(texture + n, size);
		parse->c_rgb = check_colors(parse->ceiling);
	}
}

void	parse_texture(char *texture, t_parse *parse, int size, int n)
{
	if (texture[0] == 'N' && parse->no)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'S' && parse->so)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'W' && parse->we)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'E' && parse->ea)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'F' && parse->floor)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'C' && parse->ceiling)
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
		if (parse->ceiling && parse->ea && parse->floor && parse->no
			&& parse->so && parse->we)
			break ;
		free(*line);
	}
    check_open_file(parse);
	free(*line);
}
