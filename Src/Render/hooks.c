
#include "../../Inc/cube3d.h"

void	hook_control(t_cube *cube)
{
	mlx_hook(cube->window.mlx_window, 17, 0, close_window, cube);
	// mlx_key_hook(cube->window.mlx_window, testkey, cube);
	mlx_hook(cube->window.mlx_window, 2, 1L << 0, key_press, cube);
}

int	key_press(int key_code, t_cube *cube)
{
	
	if (key_code == ESC)
		close_window(&cube->window);
	else if (key_code == RA | key_code == LA)
		player_movement(&cube->player, key_code);
	return (0);
}

void	my_mlx_pixel_put(t_window *win, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIND_WIDTH || y < 0 || y >= WIND_HEIGHT)
		return;
	dst = win->addr + (y * win->line_length + x * (win->bitpp / 8));
	*(unsigned int *)dst = color;
}

int	loop_hook(t_cube *cube)
{
	draw(cube);
	return (0);
}

int	testkey(int key_code, t_window *wind)
{
	(void)wind;
	ft_printf("key_code: %d\n", key_code);
	return (0);
}