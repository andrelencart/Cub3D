
#include "../../Inc/cube3d.h"

int	init_monster(t_cube *cube, t_parse *data)
{
	cube->enemy.monster.x = data->enemy_x + 0.5;
	cube->enemy.monster.y = data->enemy_y + 0.5;
	cube->enemy.monster.dir_x = cube->player.dir_x;
	cube->enemy.monster.dir_y = cube->player.dir_y;
	cube->enemy.monster.init_pos_x = cube->enemy.monster.x;
	cube->enemy.monster.init_pos_y = cube->enemy.monster.y;
	cube->enemy.monster.moving_backward = 0;
	cube->enemy.monster.moving_forward = 0;
	cube->enemy.monster.rot_speed = 0.05;
	cube->enemy.monster.strafing_left = 0;
	cube->enemy.monster.strafing_right = 0;
	return (0);
}
