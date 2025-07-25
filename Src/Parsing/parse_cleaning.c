#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

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
	while (data->map[i] != NULL)
		free(data->map[i++]);
	if (data->map != NULL)
		free(data->map);
	free(data);
}

/*
void	free_data(t_parse *data)
{
	int	i;

	i = 0;
	if (data->n_face != NULL)
	{
		ft_printf("data->n_face->%s\n", data->n_face);
		free(data->n_face);
	}
	if (data->s_face != NULL)
	{
		ft_printf("data->s_face->%s\n", data->s_face);
		free(data->s_face);
	}
	if (data->e_face != NULL)
	{
		ft_printf("data->e_face->%s\n", data->e_face);
		free(data->e_face);
	}
	if (data->w_face != NULL)
	{
		ft_printf("data->w_face->%s\n", data->w_face);
		free(data->w_face);
	}
	while (data->map[i] != NULL)
	{
		printf("data->map[%d]->%s\n", i, data->map[i]);
		free(data->map[i++]);
	}
	if (data->map != NULL)
	{
		printf("Limpando map\n");
		free(data->map);
	}
	printf("Limpando data\n");
	free(data);
}
*/

int	parse_error(char *msg)
{
	ft_printf_fd(STDERR_FILENO, "Error\n");
	ft_printf_fd(STDERR_FILENO, "Cube3d: %s\n", msg);
	return (1);
}
