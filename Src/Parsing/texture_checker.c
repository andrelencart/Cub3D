#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

int	assign_color(char *str, int *color, char **line)
{
	int	i;
	int	channel;
	int	tmp[3];

	i = 0;
	channel = 0;
	while (channel < 3)
	{
		while (str[i] && str[i] == ' ')
			i++;
		tmp[channel] = ft_atoi(&str[i]);
		if (tmp[channel] < 0 || tmp[channel] > 255 || *line != NULL)
			return (1);
		while (str[i] && ft_isdigit(str[i]))
			i++;
		if (channel < 2 && str[i] != ',')
			return (1);
		else
			i++;
		channel++;
	}
	*color = (tmp[0] << 16) | (tmp[1] << 8) | tmp[2];
	*line = ft_strjoin("", str);
	return (0);
}

int	assign_texture(char *str, char *dest)
{
	if (str && dest)
		return (1);
	return (0);
}

int	parse_line(t_parse *data, char *line)
{
	if (!ft_strncmp(line, "F", 1))
		return (assign_color(&line[1], &data->floor, &data->f_str));
	else if (!ft_strncmp(line, "C", 1))
		return (assign_color(&line[1], &data->ceiling, &data->c_str));
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
		{
			ft_printf_fd(STDERR_FILENO, "Error\n");
			ft_printf_fd(STDERR_FILENO, "Cube3d: .cub line %d is invalid\n", i);
			free_data(data);
			return (1);
		}
	}
	//check result
	//remove
	ft_printf("%s\n", data->c_str);
	ft_printf("%X\n", data->ceiling);
	ft_printf("%s\n", data->f_str);
	ft_printf("%X\n", data->floor);
	ft_printf("%s\n", data->e_face);
	ft_printf("%s\n", data->n_face);
	ft_printf("%s\n", data->s_face);
	ft_printf("%s\n", data->w_face);
	return (0);
}
