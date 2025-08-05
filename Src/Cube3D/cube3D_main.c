#include "../../Inc/cube3d.h"

int	main(int ac, char **av)
{
	t_parse	*data;
	t_cube	cube;

	if (ac != 2 || !av)
		return (parse_error("Wrong number of arguments"));
	data = NULL;
	if (init_parse_data(&data))
		return (1);
	if (parse_check_fname(av[1], data))
		return (free_data(data), 1);
	if (parse_textures(data))
		return (free_data(data), 1);
	init(&cube, data);
	free_data(data);
	draw(&cube);
	hook_control(&cube);
	mlx_loop_hook(cube.window.mlx, loop_hook, &cube);
	mlx_loop(cube.window.mlx);
	return (0);
}
