#ifndef PARSE_H
# define PARSE_H

# include "structs.h"

int		is_initial(char *line);
char	*add_arg(char *s);
int		check_int_color(int n);
int		create_rgb(int r, int g, int b);
int		check_colors(char *color);
void	init_texture(char *texture, t_parse *parse, int n);
int		parse_texture(char *texture, t_parse *parse, int n);
int		check_line(t_parse *parse, char *line);
void	init_parse(t_parse *parse);
t_parse	parse(char *str);

#endif