#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

int	check_line_end(char *str)
{
	while(*str == ' ')
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
