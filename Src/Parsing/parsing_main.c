#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

int	main(int ac, char **av)
{
	t_parse	*data;

	if (ac != 2 || !av)
		return (bad_parse("Wrong number of arguments"));
	data = ft_calloc(1, sizeof(t_parse));
	if (!data)
		return (bad_parse("Failed to allocate *data"));
	if (parse_check_fname(av[1], data))
		return(1);
	if (parse_textures(data))
	free_data(data);
	return (0);
}