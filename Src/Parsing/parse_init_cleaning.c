#include "../../Inc/cube3d.h"

void	free_data(t_parse *data)
{
	int	i;

	i = 0;
	if (data->n_face != NULL)
		free(data->n_face);
	if (data->s_face != NULL)
		free(data->s_face);
	if (data->e_face != NULL)
		free(data->e_face);
	if (data->w_face != NULL)
		free(data->w_face);
	while (data->map != NULL && data->map[i] != NULL)
		free(data->map[i++]);
	if (data->map != NULL)
		free(data->map);
	free(data);
}

int	parse_error(char *msg)
{
	ft_printf_fd(STDERR_FILENO, "Error\n");
	ft_printf_fd(STDERR_FILENO, "Cube3d: %s\n", msg);
	return (1);
}

int	map_error(char *msg, int ln, int cl)
{
	ft_printf_fd(STDERR_FILENO, "Error\n");
	ft_printf_fd(STDERR_FILENO, "Cube3d: %s x: %d y: %d\n", msg, cl, ln);
	return (1);
}

int	init_parse_data(t_parse	**tmp)
{
	*tmp = ft_calloc(1, sizeof(t_parse));
	if (!(*tmp))
		return (parse_error("init_parse_data: Failed to allocate *data"));
	(*tmp)->ceiling = -1;
	(*tmp)->floor = -1;
	return (0);
}
