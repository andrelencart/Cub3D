#include "../../Inc/cube3d.h"

int	move_update_flag_press(int keycode, t_cube *cube)
{
	if (keycode == W)
		cube->player.moving_forward = 1;
	else if (keycode == S)
		cube->player.moving_backward = 1;
	else if (keycode == D)
		cube->player.strafing_right = 1;
	else if (keycode == A)
		cube->player.strafing_left = 1;
	if (cube->map.grid[(int)cube->player.y][(int)cube->player.x] == 'F')
		exit_clean(cube);
	return (0);
}

int	move_update_flag_release(int keycode, t_cube *cube)
{
	if (keycode == W)
		cube->player.moving_forward = 0;
	else if (keycode == S)
		cube->player.moving_backward = 0;
	else if (keycode == D)
		cube->player.strafing_right = 0;
	else if (keycode == A)
		cube->player.strafing_left = 0;
	if (cube->map.grid[(int)cube->player.y][(int)cube->player.x] == 'F')
		exit_clean(cube);
	return (0);
}

int	player_rotation(t_player *player, int key_code)
{
	if (key_code == RA)
		rotate_player(player, player->rot_speed);
	else if (key_code == LA)
		rotate_player(player, -player->rot_speed);
	return (0);
}
