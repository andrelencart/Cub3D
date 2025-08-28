
#include "../../Inc/cube3d.h"


void	init_monster(t_player *player, t_parse *data, int map_height)
{
	(void)map_height;
	player->x = data->player_x + 0.5; // x Position
	player->y = data->player_y + 0.5; // y Position (INVERTED)
	player->dir_x = data->player_dir_x;
	player->dir_y = data->player_dir_y;
	player->init_pos_x = data->player_dir_x;
	player->init_pos_y = data->player_dir_y;
	set_player_camera_plane(player);
	player->rot_speed = 0.05; // For the Field Of View, 0.66 comonly used for the type of game
	player->moving_forward = 0;
	player->moving_backward = 0;
	player->strafing_left = 0;
	player->strafing_right = 0;
	// printf("Player spawn: x=%f, y=%f (map_height=%d)\n", player->x, player->y, map_height);
}