
#include "../../Inc/cube3d.h"

int	player_movement(t_player *player, int key_code)
{
	if (key_code == RA)
		rotate_player(player, player->rot_speed);
	else if (key_code == LA)
		rotate_player(player, -player->rot_speed);
	return (0);
}

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
