/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:37:55 by alevasse          #+#    #+#             */
/*   Updated: 2023/01/05 15:45:34 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../structs.h"

int		is_initial(char *line);
char	*add_arg(char *s, int size);
int		check_int_color(char *str);
int		create_rgb(int r, int g, int b);
int		check_colors(char *color);
void	init_texture(char *texture, t_parse *parse, int size, int n);
void	parse_texture(char *texture, t_parse *parse, int size, int n);
void	check_line(t_parse *parse, char *line);
t_parse	parse(char *str);
void	check_map_line(char *line);
int		check_empty_line(char *line);
void	get_size_map(t_parse *parse, char *line, int fd);
void	get_map(t_parse *parse, char *line, int fd, char *file);
void	check_pos(char **map, int i, int j);
void	parse_player(t_parse *parse, char *orient, int i, int j);
void	parse_wall(t_parse parse);
void	check_if_map_in_last(char **line, int fd);

#endif
