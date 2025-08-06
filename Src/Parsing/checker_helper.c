#include "../../Inc/cube3d.h"

void	assign_player_pos(t_parse *data, int i, int j)
{
	data->player_dir = data->map[i][j];
	data->player_dir_x = 0.0;
	data->player_dir_y = 0.0;
	if (data->player_dir == 'E')
		data->player_dir_x = -1.0;
	else if (data->player_dir == 'W')
		data->player_dir_x = 1.0;
	else if (data->player_dir == 'N')
		data->player_dir_y = -1.0;
	else
		data->player_dir_y = 1.0;
	data->player_x = j;
	data->player_y = i;
	data->map[i][j] = '0';
}

int	find_map(t_parse *data, int i)
{
	int	j;

	while (data->map[i] && data->map[i][0] == '\n')
		i++;
	j = 0;
	while (data->map[i][j])
	{
		if (ft_strchr(" 01NSEW\n", data->map[i][j]))
			j++;
		else
		{
			ft_printf_fd(STDERR_FILENO, "Error\n");
			ft_printf_fd(2, "Cube3d: .cub line %d is invalid\n", i + 1);
			return (1);
		}
	}
	return (0);
}

int	check_line_end(char *str)
{
	while (*str == ' ')
		str++;
	if (*str != 0 && *str != 10)
		return (1);
	return (0);
}

int	is_data_filled(t_parse *data)
{
	int	status;

	status = 0;
	if (data->ceiling == -1 || data->floor == -1)
		status |= 1;
	if (data->e_face == NULL || data->w_face == NULL || \
data->n_face == NULL || data->s_face == NULL)
		status |= 1;
	return (status);
}

int	lookfor_texture(char **dest)
{
	char	*tmp;
	int		i;
	int		fd;

	i = 0;
	tmp = NULL;
	while ((*dest)[i] && (*dest)[i] != ' ' && (*dest)[i] != 10)
		i++;
	tmp = ft_calloc(i + 1, sizeof(char));
	if (!tmp)
	{
		ft_printf_fd(STDERR_FILENO, "Error\nCube3d: Could not allocate ");
		return (ft_putstr_fd(*dest, 2), 1);
	}
	ft_strlcpy(tmp, *dest, i + 1);
	free(*dest);
	*dest = tmp;
	fd = open(*dest, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(STDERR_FILENO, "Error\nCube3d: \"%s\": ", *dest);
		return (ft_putendl_fd(strerror(errno), 2), 1);
	}
	close(fd);
	return (0);
}
