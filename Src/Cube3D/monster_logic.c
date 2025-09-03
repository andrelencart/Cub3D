#include "../../Inc/cube3d.h"

void	monster_logic(t_cube *cube)
{
	if (cube->frame_time < 0)
		cube->enemy.anim_time = 0;
	else
		cube->enemy.anim_time += cube->frame_time;
	if (cube->enemy.anim_time >= cube->enemy.anim_speed)
	{
		cube->enemy.frame++;
		if (cube->enemy.frame >= 4)
			cube->enemy.frame = 0;
		cube->enemy.anim_time = 0;
	}
}
