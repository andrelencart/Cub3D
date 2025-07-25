#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

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
		return (ft_putstr_fd(*dest, 2), write(2, "\n", 1), 1);
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
