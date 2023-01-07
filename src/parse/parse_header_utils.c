/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:48:57 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/05 15:43:00 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

#include "../utils.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
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
