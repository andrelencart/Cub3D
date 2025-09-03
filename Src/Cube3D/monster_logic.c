#include "../../Inc/cube3d.h"

void	enemy_wander(t_cube *cube, t_enemy *enemy)
{
	double	n_x;
	double	n_y;
	double	angle;
	double	delta;

	enemy->speed = 0.5;
	n_x = enemy->monster.x + enemy->monster.dir_x * enemy->speed * \
cube->frame_time;
	n_y = enemy->monster.y + enemy->monster.dir_y * enemy->speed * \
cube->frame_time;
	if (!can_move(cube, n_x, enemy->monster.y, 0.2) || \
!can_move(cube, enemy->monster.x, n_y, 0.2))
	{
		angle = atan2(enemy->monster.dir_y, enemy->monster.dir_x);
		delta = ((rand() % 180) - 90) * (PI / 90.0);
		angle = PI + delta;
		enemy->monster.dir_x = cos(angle);
		enemy->monster.dir_y = sin(angle);
	}
	else
	{
		enemy->monster.x = n_x;
		enemy->monster.y = n_y;
	}
}

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
	if (cube->enemy.state == 0)
		enemy_wander(cube, &cube->enemy);
}
