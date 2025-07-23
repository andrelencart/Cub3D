#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

int	assign_color(char *str, int *color)
{
	int	i;

	i = 1;
	while (str[i] == ' ')
		i++;
	if (!ft_isdigit(str[i]))
		return (1);
}

int	assign_texture(char *str, char *dest)
{}

int	parse_line(t_parse *data, char *line)
{
	if (!ft_strncmp(line, "F", 1))
		return (assign_color(&line[1], &data->floor));
	else if (!ft_strncmp(line, "C", 1))
		return (assign_color(&line[1], &data->ceiling));
	else if (!ft_strncmp(line, "NO", 2))
		return (assign_texture(&line[2], data->n_face));
	else if (!ft_strncmp(line, "SO", 2))
		return (assign_texture(&line[2], data->s_face));
	else if (!ft_strncmp(line, "WE", 2))
		return (assign_texture(&line[2], data->w_face));
	else if (!ft_strncmp(line, "EA", 2))
		return (assign_texture(&line[2], data->e_face));
	else
		return (1);
}

int	parse_textures(t_parse *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] == ' ')
			j++;
		if (data->map[i][j] == 10 || !parse_line(data, &data->map[i][j]))
			i++;
		else
			return (free_data(data), bad_parse("Invalid line in .cub", NULL));
	}
	return (0);
}
