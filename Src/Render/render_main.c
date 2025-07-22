

#include "../../Inc/cube3d.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_cube	cube;

	if (ac != 2)
		return (ft_printf("%s\n", ERROR_ARGS), 1);
	init_window(&cube.window);
	hook_control(&cube);
	mlx_loop(cube.window.mlx);
	
}
