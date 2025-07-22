

#include "../../Inc/cube3d.h"

void	init_window(t_window *window)
{
	window->mlx = mlx_init();
	window->mlx_window = mlx_new_window(window->mlx, WIDTH, \
		HEIGHT, "CUBE3D");
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	window->addr = mlx_get_data_addr(window->img, &window->bitpp, \
		&window->line_length, &window->endian);
}

int	close_window(t_window *window)
{
	mlx_destroy_image(window->mlx, window->img);
	mlx_destroy_window(window->mlx, window->mlx_window);
	mlx_destroy_display(window->mlx);
	free(window->mlx);
	exit(0);
}