#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

int	assign_color(char *str, int *color)
{
	int	move;

	move = 16;
	if (*color > -1)
		return (1);
	*color = 0;
	while (move >= 0)
	{
		while (*str && *str == ' ')
			str++;
		if (!ft_isdigit(*str) || ft_atoi(&(*str)) < 0 || \
					ft_atoi(&(*str)) > 255)
			return (1);
		*color |= (ft_atoi(str)) << move;
		while (*str && ft_isdigit(*str))
			str++;
		if (move > 0 && *str != ',')
			return (1);
		else
			str++;
		move = move - 8;
	}
	return (check_line_end(str));
}

int	assign_texture(char *str, char **dest)
{
	*dest = ft_strdup(str);
	return (0);
}

int	parse_line(t_parse *data, char *line)
{
	if (!ft_strncmp(line, "F", 1))
		return (assign_color(&line[1], &data->floor));
	else if (!ft_strncmp(line, "C", 1))
		return (assign_color(&line[1], &data->ceiling));
	else if (!ft_strncmp(line, "NO", 2))
		return (assign_texture(&line[2], &data->n_face));
	else if (!ft_strncmp(line, "SO", 2))
		return (assign_texture(&line[2], &data->s_face));
	else if (!ft_strncmp(line, "WE", 2))
		return (assign_texture(&line[2], &data->w_face));
	else if (!ft_strncmp(line, "EA", 2))
		return (assign_texture(&line[2], &data->e_face));
	else
		return (1);
}

int	parse_textures(t_parse *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i] && is_data_filled(data))
	{
		while (data->map[i][j] == 10)
			i++;
		if (!parse_line(data, &data->map[i][j]))
			i++;
		else
		{
			ft_printf_fd(STDERR_FILENO, "Error\n");
			ft_printf_fd(2, "Cube3d: .cub line %d is invalid\n", i + 1);
			return (1);
		}
	}
	return (0);
}
