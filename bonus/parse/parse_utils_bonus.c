/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:14:29 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/05 15:44:35 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

#include "../structs_bonus.h"
#include "../utils_bonus.h"
#include "parse_bonus.h"

int	is_initial(char *line)
{
	if (line[0] == 'N' || line[0] == 'S')
	{
		if (line[1] == 'O')
			return (2);
		return (1);
	}
	else if (line[0] == 'E')
	{
		if (line[1] == 'A')
			return (2);
		return (1);
	}
	else if (line[0] == 'W')
	{
		if (line[1] == 'E')
			return (2);
		return (1);
	}
	else if (line[0] == 'F' || line[0] == 'C')
		return (1);
	else
		return (0);
}

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}

int	check_arg(char *line, int initial)
{
	char	**tmp;
	int		size;

	size = 0;
	tmp = ft_split(line + initial, ' ');
	if (ft_strchr(tmp[0], '\n'))
	{
		if (tmp[0][0] == '\n')
		{
			ft_free_tab(tmp, ft_strlen_tab(tmp));
			error_exit("Error\nInvalid texture argument\n");
		}
		size = ft_strlen(tmp[0]) - 1;
	}
	else if (tmp[1][0] == '\n')
		size = ft_strlen(tmp[0]);
	else
	{
		ft_free_tab(tmp, ft_strlen_tab(tmp));
		error_exit("Error\nInvalid texture argument\n");
	}
	ft_free_tab(tmp, ft_strlen_tab(tmp));
	return (size);
}

void	check_line(t_parse *parse, char *line)
{
	int	i;
	int	n;

	i = -1;
	while (line[++i] == ' ')
		;
	if (line[i] == '\n')
		return ;
	n = is_initial(line + i);
	if (n == 0)
	{
		free(line);
		error_exit("Error\nInvalid texture initials\n");
	}
	parse_texture(line + i, parse, check_arg(line, n), n);
}
