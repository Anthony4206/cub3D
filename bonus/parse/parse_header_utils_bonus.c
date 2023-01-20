/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:48:57 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/20 15:02:16 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fcntl.h>

#include "parse_bonus.h"
#include "../structs_bonus.h"
#include "../utils_bonus.h"

void	init_texture(char *texture, t_parse *parse, int size, int n)
{
	if (texture[0] == 'N')
		parse->n = add_arg(texture + n, size);
	else if (texture[0] == 'S')
		parse->s = add_arg(texture + n, size);
	else if (texture[0] == 'E')
		parse->e = add_arg(texture + n, size);
	else if (texture[0] == 'W')
		parse->w = add_arg(texture + n, size);
	else if (texture[0] == 'F')
	{
		parse->f = add_arg(texture + n, size);
		parse->f_rgb = check_colors(parse->f);
	}
	else if (texture[0] == 'C')
	{
		parse->c = add_arg(texture + n, size);
		parse->c_rgb = check_colors(parse->c);
	}
}

void	parse_texture(char *texture, t_parse *parse, int size, int n)
{
	if (texture[0] == 'N' && parse->n)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'S' && parse->s)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'W' && parse->w)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'E' && parse->e)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'F' && parse->f)
		error_exit("Error\nTexture specified more than once\n");
	else if (texture[0] == 'C' && parse->c)
		error_exit("Error\nTexture specified more than once\n");
	init_texture(texture, parse, size, n);
}

void	check_door_xpm(void)
{
	if (open("./texture/doors/door_0.xpm", O_RDONLY) == -1)
		error_exit("Error\nInvalid door's texture file name\n");
	if (open("./texture/doors/door_4.xpm", O_RDONLY) == -1)
		error_exit("Error\nInvalid door's texture file name\n");
}

void	check_open_file(t_parse *parse)
{
	if (open(parse->n, O_RDONLY) == -1)
		error_exit("Error\nInvalid texture file name\n");
	if (open(parse->s, O_RDONLY) == -1)
		error_exit("Error\nInvalid texture file name\n");
	if (open(parse->e, O_RDONLY) == -1)
		error_exit("Error\nInvalid texture file name\n");
	if (open(parse->w, O_RDONLY) == -1)
		error_exit("Error\nInvalid texture file name\n");
	check_door_xpm();
}

char	*add_arg(char *s, int size)
{
	int		i;
	int		j;
	char	*ret;

	i = -1;
	ret = ft_calloc(sizeof(char), size + 1);
	while (s[++i] == ' ')
		;
	j = 0;
	while (s[i] && (s[i] != ' ' && s[i] != '\n' && s[i] != '\0'))
		ret[j++] = s[i++];
	return (ret);
}
