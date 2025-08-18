
#include "../../Inc/cube3d.h"

int	rotate_player(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_player_x;

	old_dir_x = player->dir_x;
	old_player_x = player->plane_x;

	player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);

	player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
	player->plane_y = old_player_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
	
	// printf("Rotated: dir_x=%.2f dir_y=%.2f plane_x=%.2f plane_y=%.2f\n", player->dir_x, player->dir_y, player->plane_x, player->plane_y);
	return (0);
}

// int	mouse_move_handler(int x, int y, t_cube *cube)
// {
// 	int			center_x;
// 	int			center_y;
// 	double		sensitivity;
// 	int			delta_x;
// 	static int	last_x = -1;
// 	static int ignore_next = 0;

// 	(void)y;
// 	center_x = WIND_WIDTH / 2;
// 	sensitivity = 0.0015;
// 	delta_x = x - center_x;
// 	center_y = WIND_HEIGHT / 2;
// 	if (ignore_next)
// 	{
// 		last_x = x;
// 		ignore_next = 0;
// 		return (0);
// 	}
// 	if (last_x == -1)
// 	{
// 		last_x = x;
// 		return (0);
// 	}
// 	delta_x = x - last_x;
// 	last_x = x;
// 	if (delta_x != 0)
// 		rotate_player(&cube->player, -delta_x * sensitivity);
// 	if (x <= 0 || x >= WIND_WIDTH - 1 ||
// 		y <= 0 || y >= WIND_HEIGHT - 1)
// 	{
// 		mlx_mouse_move(cube->window.mlx, cube->window.mlx_window, center_x, center_y);
// 		// last_x = center_x;
// 		ignore_next = 1;
// 	}
// 	return (0);
// }

int mouse_move_handler(int x, int y, t_cube *cube)
{
	double sensitivity = 0.0015;
	static int last_x = -1;
	int delta_x;

	(void)y;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	if (x <= 0)
	{
		rotate_player(&cube->player, sensitivity * 10); // The multiplier controls speed
		last_x = x;
		return (0);
	}	
	if (x >= WIND_WIDTH - 1)
	{
		rotate_player(&cube->player, -sensitivity * 10);
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	last_x = x;
	if (delta_x != 0)
		rotate_player(&cube->player, -delta_x * sensitivity);
	return (0);
}

int	player_move_front_back(t_player *player, char **map, double frame_time, int map_height)
{
	double	move_speed;
	double	new_x;
	double	new_y;
	(void) map;

	move_speed = frame_time * 0.5;
	if (player->moving_forward)
	{
		// printf("entrou move front\n");
		new_x = player->x + player->dir_x * move_speed;
		new_y = player->y + player->dir_y * move_speed;
		if (map[map_height - 1 - (int)player->y][(int)new_x] != '1')
			player->x = new_x;
		if (map[map_height - 1 - (int)new_y][(int)player->x] != '1')
			player->y = new_y;
	}
	if (player->moving_backward)
	{
		// printf("entrou move back\n");
		new_x = player->x - player->dir_x * move_speed;
		new_y = player->y - player->dir_y * move_speed;
		if (map[map_height - 1 - (int)player->y][(int)new_x] != '1')
			player->x = new_x;
		if (map[map_height - 1 - (int)new_y][(int)player->x] != '1')
			player->y = new_y;
	}
	return (0);
}

int	player_move_left_right(t_player *player, char **map, double frame_time, int map_height)
{
	double	move_speed;
	double	new_x;
	double	new_y;
	(void) map;

	move_speed = frame_time * 0.5;
	if (player->strafing_right)
	{
		// printf("entrou move right\n");
		new_x = player->x + player->plane_x * move_speed;
		new_y = player->y + player->plane_y * move_speed;
		if (map[map_height - 1 - (int)player->y][(int)new_x] != '1')
			player->x = new_x;
		if (map[map_height - 1 - (int)new_y][(int)player->x] != '1')
			player->y = new_y;
	}
	if (player->strafing_left)
	{
		// printf("entrou move left\n");
		new_x = player->x - player->plane_x * move_speed;
		new_y = player->y - player->plane_y * move_speed;
		if (map[map_height - 1 - (int)player->y][(int)new_x] != '1')
			player->x = new_x;
		if (map[(int)new_y][(int)player->x] != '1')
			player->y = new_y;
	}
	return (0);
}
