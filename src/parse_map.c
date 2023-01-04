#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "utils.h"
#include "structs.h"

void	check_map_line(char *line)
{
	int	        i;

	i = 0;
	while (line[i])
	{
        if (!ft_strchr("NSEW01 \n\t", line[i]))
		{
			printf("ERORR CHAR=%c.\n", line[i]);
			free(line);
			error_exit("Error\nInvalid map format\n");
		}
		i++;
	}
}

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void	check_if_map_in_last(char *line, int fd)
{
	if (check_empty_line(line))
	{
		while (1)
		{
			free(line);
			line = get_next_line(fd);
			if (!line || !check_empty_line(line))
				break ;
		}
		if (!check_empty_line(line))
			error_exit("Error\nMap not finishing item\n");
	}
}

void	get_size_map(t_parse *parse, int fd)
{
	char	*line;
	int		size;
	int		i;

	parse->map_height = 0;
	parse->map_width = 0;
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (check_empty_line(line))
			break ;
		i++;
	}
	while (1)
	{
		if (!check_empty_line(line))
			break ;
		parse->map_height++;
		size = ft_strlen(line);
		if (line[size - 1] == '\n')
			size--;
		if (size > parse->map_width)
			parse->map_width = size;
		check_map_line(line);
		free(line);
		line = get_next_line(fd);
	}
	printf("CHECK map_height = %d\n", parse->map_height);
	printf("CHECK map_width = %d\n", parse->map_width);
	check_if_map_in_last(line, fd);
	close(fd);
}

void	get_map(t_parse *parse, int fd, char *file)
{
	int	    i;
    int     j;
	char	*line;

    i = -1;
	get_size_map(parse, fd);
	fd = open(file, O_RDONLY);
	parse->map = ft_calloc(sizeof(char *), parse->map_height + 1);
    while (++i < parse->map_height)
        parse->map[i] = ft_calloc(sizeof(char), parse->map_width + 1);
    j = 6;
    while (1)
    {
		line = get_next_line(fd);
        if (check_empty_line(line))
            j--;
        if (j == 0)
            break ;
    }
	line = get_next_line(fd);
    while (!check_empty_line(line))
	    line = get_next_line(fd);
	i = -1;
    while (++i < parse->map_height)
	{
  	    ft_strlcat(parse->map[i], line, -1);
        j = ft_strlen(line) - 2;
//        printf("map_wight : %d\n", parse->map_width);
        if (!parse->map[i][parse->map_width])
        {
//            printf("!\n");
            j++;
        }
 //       printf("j : %d\n", j);
        while (++j < parse->map_width)
            parse->map[i][j - 1] = ' ';
        parse->map[i][j] = '\0';
 //       printf("i : %d : %s\n", i, parse->map[i]);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}
