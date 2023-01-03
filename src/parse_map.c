#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "utils.h"
#include "structs.h"

void	check_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
			|| line[i] == '0' || line[i] == '1' || line[i] == ' ' || line[i] == '	' 
			|| line[i] == '\n'))
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
	if (!line || line[0] == '\0')
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
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
		if (!check_empty_line(line))
			break ;
		i++;
	}
	parse->line_map_start = i;
	while (1)
	{
		if (!line || check_empty_line(line))
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
	int	i;
	char	*line;

	i = 0;
	get_size_map(parse, fd);
	fd = open(file, O_RDONLY);
	parse->map = malloc(sizeof(char *) * (parse->map_height + 1));
	while (i++ < parse->line_map_start)
		line = get_next_line(fd);
	i = 0;
	while (1)
	{
		if (!line || line[0] == '\n')
			break ;
		parse->map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	//if (line[0] == '\n')
}
