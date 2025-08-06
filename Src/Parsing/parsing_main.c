#include "../../Inc/cube3d.h"

int	main(int ac, char **av)
{
	t_parse	*data;

	if (ac != 2 || !av)
		return (parse_error("Wrong number of arguments"));
	data = NULL;
	if (init_parse_data(&data))
		return (1);
	if (parse_check_fname(av[1], data))
		return (free_data(data), 1);
	if (parse_cub(data))
		return (free_data(data), 1);
	if (square_map(data))
		return (free_data(data), 1);
	free_data(data);
	return (0);
}
