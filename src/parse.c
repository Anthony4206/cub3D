#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "utils.h"
#include "structs.h"
#include "parse_map.h"

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

char	*add_arg(char *s)
{
	int	i;

	i = -1;
	while (s[++i] == ' ');

	return (ft_strdup(s + i));
}

int	check_int_color(int n)
{
	int	size;

	size = 1;
	if (n < 0)
		error_exit("Error\nInvalid RGB code (neg int)\n");
	while (n > 9)
	{
		n /= 10;
		size++;
	}
	if (size > 3)
		error_exit("Error\nInvalid RGB code\n");
	if (n > 255)
		error_exit("Error\nInvalid RGB code\n");
	return (n);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	check_colors(char *color)
{
	int	i;
	int	r;
	int g;
	int b;

	i = -1;
	r = check_int_color(ft_atoi(color));
	while (ft_isdigit(color[++i]));
	if (!(color[i] == ',' && ft_isdigit(color[i + 1])))
		error_exit("Error\nInvalid color code\n");
	i++;
	g = check_int_color(ft_atoi(color + i));
	while (ft_isdigit(color[++i]));
	if (!(color[i] == ',' && ft_isdigit(color[i + 1])))
		error_exit("Error\nInvalid color code\n");
	i++;
	b =check_int_color(ft_atoi(color));
	while (color[++i] == ' ');
	if (color[i] != '\n')
		error_exit("Error\nInvalid color code\n");
	return (create_rgb(r, g, b));
}

void	init_texture(char *texture, t_parse *parse, int n)
{
	if (texture[0] == 'N')
		parse->N = add_arg(texture + n);
	else if (texture[0] == 'S')
		parse->S = add_arg(texture + n);
	else if (texture[0] == 'E')
		parse->E = add_arg(texture + n);
	else if (texture[0] == 'W')
		parse->W = add_arg(texture + n);
	else if (texture[0] == 'F')
	{
		parse->F = add_arg(texture + n);
		parse->F_RGB = check_colors(parse->F);
	}
	else if (texture[0] == 'C')
	{
		parse->C = add_arg(texture + n);
		parse->C_RGB = check_colors(parse->F);
	}
}

void	parse_texture(char *texture, t_parse *parse, int n)
{
	if (texture[0] == 'N' && parse->N)
		error_exit("Error: texture specified more than once\n");
	else if (texture[0] == 'S' && parse->S)
		error_exit("Error: texture specified more than once\n");
	else if (texture[0] == 'W' && parse->W)
		error_exit("Error: texture specified more than once\n");
	else if (texture[0] == 'E' && parse->E)
		error_exit("Error: texture specified more than once\n");
	else if (texture[0] == 'F' && parse->F)
		error_exit("Error: texture specified more than once\n");
	else if (texture[0] == 'C' && parse->C)
		error_exit("Error: texture specified more than once\n");
	init_texture(texture, parse, n);
}

void	check_line(t_parse *parse, char *line)
{
	int	i;
	int	n;
	
	i = -1;
	while (line[++i] == ' ');
	if (line[i] == '\n')
		return ;
	n = is_initial(line + i);
	if (n == 0)
	{
		printf("LINE =%s\n", line);
		free(line);
		error_exit("Error\nInvalid texture initials\n");
	}
	parse_texture(line + i, parse, n);
	i += n;
}

void    check_pos(char **map, int i, int j)
{
    if (map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' '
        || map[i - 1][j + 1] == ' ' || map[i][j - 1] == ' '
        || map[i][j + 1] == ' ' || map[i + 1][j - 1] == ' '
        || map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ')
        error_exit("Error\nMap is not close\n");
}

void    parse_wall(t_parse ctx)
{
    int i;
    int j;

    i = -1;
    while (++i < ctx.map_height)
    {
        j = -1;
        while (++j < ctx.map_width)
        {
            if (i == 0 || i == ctx.map_height - 1)
            {
                if (ctx.map[i][j] != ' ' && ctx.map[i][j] != '1')
                    error_exit("Error\nMap is not close\n");
            }
            else
            {
                if (!ft_strchr(" 1", ctx.map[i][0])
                    || !ft_strchr(" 1", ctx.map[i][ctx.map_width - 1]))
                    error_exit("Error\nMap is not close\n");
                if (ft_strchr("NSEW0", ctx.map[i][j]))
                    check_pos(ctx.map, i, j);
            }
        }
    }
}

t_parse	parse(char *str)
{
	t_parse	ret;
	int		fd;
	char	*line;

	ft_bzero(&ret, sizeof(t_parse));
	fd = open(str, O_RDONLY);
	if (fd == -1)
		error_exit("Error\nInvalid map name\n");
	if (ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4))
		error_exit("Error\nInvalid map format 1\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		check_line(&ret, line);	
		if (ret.C && ret.E && ret.F && ret.N && ret.S && ret.W)
		{
			free(line);
			break ;
		}
		free(line);
	}
	get_map(&ret, fd, str);
    parse_wall(ret);
	return (ret);
	//si erreur:
		//print un message d'erreur approprié
		//fermeture du fichier
		//return (-1);
	/*IMPORTANT*/
	/****
     * on vérifie le format RGB et on valide les info (6 lignes avec les bons initials)
     * attention aux doublons
     * vérifier les informations qui suivent les initials 
     * liste : bon format après P et C, pas de virgule en trop, over int, chiffre supérieur à 255
     * il ne doit pas y avoir de valeur supérieur ou inférieur à int max ou int min
     * il ne dois pas y avoir de virgule
	 * on élimine les lignes vides entre les types d'élément
	 * les lignes vides dans la description de la map sont des erreurs
     * que la map est bien présente et bien à la fin du fichier
     * 
	 * les informations de chaque élément peuvent être séparées par un ou plusieurs espace
	 * La map doit être fermée/entourée de murs (1)
	 * La description de la map accepte les espaces (s'ils sont utilisés intelligement)
	 * les espaces ne doivent pas être éliminés lorsque on parse la map
	 * La map ne doit pas utiliser de caractères interdits (sont autorisés: "01NSEW")
	 * Il ne doit y avoir qu'une seule position de départ (soit: N, S, E ou W)
     * Il doit forcément y avoir un joueur
    ****/

	//fermeture du fichier
	//return 0 si pas d'erreur.
}


