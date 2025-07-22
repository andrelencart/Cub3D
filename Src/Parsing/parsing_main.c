#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

int	main(int ac, char **av)
{
	t_parse	*data;

	if (ac != 2 || !av)
		return (parse_error("Wrong number of arguments"));
	data = ft_calloc(1, sizeof(t_parse));
	if (!data)
		return (parse_error("Failed to allocate *data"));
	if (parse_check_fname(av[1], data))
		return(1);
	free_data(data);
	return (0);
}