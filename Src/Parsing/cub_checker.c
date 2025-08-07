#include "../../Inc/cube3d.h"

//copying fname to data->map.
int	get_data(char *fname, t_parse *data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	line = ft_strdup(fname);
	if (!line)
		return (parse_error("get_data: Failed to allocate *line", 0));
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (parse_error(line, strerror(errno)), free(line), 1);
	while (line != NULL)
	{
		if (i == 0)
			free(line);
		line = get_next_line(fd);
		data->map[i++] = line;
	}
	close(fd);
	return (0);
}

//Verify that fname exists, can be read and allocating memory to **map
int	find_file(char *fname, t_parse *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	line = ft_strdup(fname);
	if (!line)
		return (parse_error("find_file: Failed to allocate *line", 0));
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (parse_error(line, strerror(errno)), free(line), 1);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	if (i < 10)
		return (parse_error("Not enough lines for valid map", 0));
	data->map = ft_calloc(i + 1, sizeof(char *));
	if (!data->map)
		return (parse_error("find_file: Failed to allocate data->map", 0));
	return (get_data(fname, data));
}

//verify that fname is .cub and has a min size
int	parse_check_fname(char *fname, t_parse *data)
{
	int	len;

	len = ft_strlen(fname);
	if (len < 5 || ft_strncmp(&fname[len - 4], ".cub", 4))
		return (parse_error(fname, "File name is not valid"));
	return (find_file(fname, data));
}
