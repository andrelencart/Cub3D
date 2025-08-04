
#include "../../Inc/cube3d.h"

void	hook_control(t_cube *cube)
{
	mlx_hook(cube->window.mlx_window, 17, 0, close_window,  &cube->window);
	mlx_key_hook(cube->window.mlx_window, testkey, cube);
	mlx_hook(cube->window.mlx_window, 2, 1L<<0, key_press, cube);
	mlx_hook(cube->window.mlx_window, 3, 1L<<1, key_release, cube);
}

int	key_press(int key_code, t_cube *cube)
{
	if (key_code == ESC)
		close_window(&cube->window);
	else if (key_code == RA || key_code == LA)
		player_rotation(&cube->player, key_code);
	else if (key_code == W || key_code == A || \
		key_code == S || key_code == D)
		move_update_flag_press(key_code, cube);
	return (0);
}

int	key_release(int key_code, t_cube *cube)
{
	if (key_code == W || key_code == A || \
		key_code == S || key_code == D)
		 move_update_flag_release(key_code, cube);
	return (0);
}

void	update_frame_time(t_cube *cube)
{
	struct timeval	current_time;
	double			seconds;
	
	gettimeofday(&current_time, NULL);
	seconds = (current_time.tv_sec - cube->last_time.tv_sec)
			+ (current_time.tv_usec - cube->last_time.tv_usec) / 1000000.0;
	cube->frame_time = seconds;
	cube->last_time = current_time;
}

int	loop_hook(t_cube *cube)
{
	update_frame_time(cube);
	player_move_front_back(&cube->player, cube->map.grid, cube->frame_time);
	player_move_left_right(&cube->player, cube->map.grid, cube->frame_time);
	draw(cube);
	return (0);
}
