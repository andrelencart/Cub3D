#include "../../Inc/cube3d.h"

int	find_textures(t_parse *data)
{
	if (lookfor_texture(&data->n_face))
		return (1);
	if (lookfor_texture(&data->s_face))
		return (1);
	if (lookfor_texture(&data->e_face))
		return (1);
	if (lookfor_texture(&data->w_face))
		return (1);
	return (0);
}

int	assign_color(char *str, int *color)
{
	int	move;

	move = 16;
	if (*color > -1)
		return (1);
	*color = 0;
	while (*str && *str == ' ')
		str++;
	while (move >= 0)
	{
		if (!ft_isdigit(*str) || ft_atoi(str) < 0 || ft_atoi(str) > 255)
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
	if (*dest)
		return (1);
	while (*str && *str == ' ')
		str++;
	if (ft_strncmp(str, "./", 2))
		return (1);
	*dest = ft_strdup(str);
	if (!(*dest))
		return (2);
	str += 2;
	if (*str == 0 || *str == ' ' || *str == 10)
		return (1);
	while (*str && *str != ' ' && *str != 10)
		str++;
	while (*str && (*str == ' ' || *str == 10))
		str++;
	if (*str && (*str != ' ' || *str != 10))
		return (1);
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
	int	res;

	i = 0;
	while (data->map[i] && is_data_filled(data))
	{
		while (data->map[i] && data->map[i][0] == 10)
			i++;
		if (!data->map[i])
			return (parse_error("Map is has incomplete information"));
		res = parse_line(data, data->map[i]);
		if (res == 1)
		{
			ft_printf_fd(STDERR_FILENO, "Error\n");
			ft_printf_fd(2, "Cube3d: .cub line %d is invalid\n", i + 1);
			return (1);
		}
		else if (res == 2)
			return (parse_error("assign_texture: Failed memory allocation"));
		i++;
	}
	if (find_map(data, i) || find_textures(data) || load_map(data, i))
		return (1);
	return (0);
}
