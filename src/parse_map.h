#ifndef PARSE_MAP_H
# define PARSE_MAP_H

# include "structs.h"

void	check_map_line(char *line);
int	check_empty_line(char *line);
void	get_size_map(t_parse *parse, int fd);
void	get_map(t_parse *parse, int fd, char *file);


#endif