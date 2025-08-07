
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
