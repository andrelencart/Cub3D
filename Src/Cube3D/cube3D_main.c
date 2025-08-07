#include "../../Inc/cube3d.h"

int	main(int ac, char **av)
{
	t_parse	*data;
	t_cube	cube;

	if (ac != 2 || !av)
		return (parse_error("Wrong number of arguments", 0));
	data = NULL;
	if (init_parse_data(&data))
		return (1);
	if (parse_check_fname(av[1], data))
		return (free_data(data), 1);
	if (parse_cub(data))
		return (free_data(data), 1);
	if (square_map(data))
		return (free_data(data), 1);
	init(&cube, data);
	draw(&cube);
	hook_control(&cube);
	mlx_loop_hook(cube.window.mlx, loop_hook, &cube);
	mlx_loop(cube.window.mlx);
	free_data(data);//Either strdup map or get a special free data in success
	return (0);
}
