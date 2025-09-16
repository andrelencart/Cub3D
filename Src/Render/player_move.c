#include "../../Inc/cube3d.h"

int	rotate_player(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_player_x;

	old_dir_x = player->dir_x;
	old_player_x = player->plane_x;
	player->dir_x = player->dir_x * cos(rot_speed) \
- player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed) \
+ player->dir_y * cos(rot_speed);
	player->plane_x = player->plane_x * cos(rot_speed) \
- player->plane_y * sin(rot_speed);
	player->plane_y = old_player_x * sin(rot_speed) \
+ player->plane_y * cos(rot_speed);
	return (0);
}

int	mouse_move_handler(int x, int y, t_cube *cube)
{
	static int	last_x = -1;
	int			delta_x;

	(void)y;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	window_edge_rotation(&last_x, x, cube, SENSITIVITY);
	delta_x = x - last_x;
	last_x = x;
	if (delta_x != 0)
		rotate_player(&cube->player, delta_x * SENSITIVITY);
	return (0);
}

int	window_edge_rotation(int *last_x, int x, t_cube *cube, double sensitivity)
{
	if (x <= 0)
	{
		rotate_player(&cube->player, -sensitivity * 10);
		*last_x = x;
		return (0);
	}
	if (x >= WIND_WIDTH - 1)
	{
		rotate_player(&cube->player, sensitivity * 10);
		*last_x = x;
		return (0);
	}
	return (0);
}

int	player_move_front_back(t_player *player, t_cube *cube, double frame_time)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = frame_time * MOVE_SPEED;
	if (player->moving_forward)
	{
		new_x = player->x + player->dir_x * move_speed;
		new_y = player->y + player->dir_y * move_speed;
		if (can_move(cube, new_x, player->y, PLAYER_COLL_RAD))
			player->x = new_x;
		if (can_move(cube, player->x, new_y, PLAYER_COLL_RAD))
			player->y = new_y;
	}
	if (player->moving_backward)
	{
		new_x = player->x - player->dir_x * move_speed;
		new_y = player->y - player->dir_y * move_speed;
		if (can_move(cube, new_x, player->y, PLAYER_COLL_RAD))
			player->x = new_x;
		if (can_move(cube, player->x, new_y, PLAYER_COLL_RAD))
			player->y = new_y;
	}
	return (0);
}

int	player_move_left_right(t_player *player, t_cube *cube, double frame_time)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = frame_time * MOVE_SPEED;
	if (player->strafing_right)
	{
		new_x = player->x + player->plane_x * move_speed;
		new_y = player->y + player->plane_y * move_speed;
		if (can_move(cube, new_x, player->y, PLAYER_COLL_RAD))
			player->x = new_x;
		if (can_move(cube, player->x, new_y, PLAYER_COLL_RAD))
			player->y = new_y;
	}
	if (player->strafing_left)
	{
		new_x = player->x - player->plane_x * move_speed;
		new_y = player->y - player->plane_y * move_speed;
		if (can_move(cube, new_x, player->y, PLAYER_COLL_RAD))
			player->x = new_x;
		if (can_move(cube, player->x, new_y, PLAYER_COLL_RAD))
			player->y = new_y;
	}
	return (0);
}
