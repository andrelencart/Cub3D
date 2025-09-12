#include "../../Inc/cube3d.h"

void	enemy_chase(t_cube *cube, t_enemy *enemy)
{
	double	n_x;
	double	n_y;
	double	dis_sq;

	enemy->monster.dir_x = enemy->last_x - enemy->monster.x;
	enemy->monster.dir_y = enemy->last_y - enemy->monster.y;
	dis_sq = pow(enemy->monster.dir_x, 2.0) + pow(enemy->monster.dir_y, 2.0);
	if (sqrt(dis_sq) <= 0.3)
	{
		enemy->anim_speed = 0.09;
		enemy->state = GAME_OVER;
	}
	enemy->monster.dir_x /= sqrt(dis_sq);
	enemy->monster.dir_y /= sqrt(dis_sq);
	n_x = enemy->monster.x + enemy->monster.dir_x * enemy->speed * \
cube->frame_time;
	n_y = enemy->monster.y + enemy->monster.dir_y * enemy->speed * \
cube->frame_time;
	if (can_move(cube, n_x, enemy->monster.y, 0.2))
		enemy->monster.x = n_x;
	if (can_move(cube, enemy->monster.x, n_y, 0.2))
		enemy->monster.y = n_y;
}

void	enemy_wander(t_cube *cube, t_enemy *enemy)
{
	double	n_x;
	double	n_y;
	double	angle;
	double	delta;

	n_x = enemy->monster.x + enemy->monster.dir_x * enemy->speed * \
cube->frame_time;
	n_y = enemy->monster.y + enemy->monster.dir_y * enemy->speed * \
cube->frame_time;
	if (!can_move(cube, n_x, enemy->monster.y, 0.2) || \
!can_move(cube, enemy->monster.x, n_y, 0.2))
	{
		angle = atan2(enemy->monster.dir_y, enemy->monster.dir_x);
		delta = ((rand() % 180) - 90) * (PI / 100.0);
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

void	dda_monster_loop(t_ray *ray, t_cube *cube, double dis_sqrt)
{
	double dx;
	double dy;
	double ray_dist;

	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (raycast_wall_hit(ray, cube->map.height, cube->map.width) == 1)
			break;
		if (ft_strchr("1D", cube->map.grid[ray->map_y][ray->map_x]))
			break;
		dx = ray->map_x + 0.5 - cube->enemy.monster.x;
		dy = ray->map_y + 0.5 - cube->enemy.monster.y;
		ray_dist = sqrt(pow(dx, 2.0) + pow(dy, 2.0));
		if (ray_dist >= dis_sqrt - 0.2)
		{
			cube->enemy.last_x = cube->player.x;
			cube->enemy.last_y = cube->player.y;
			cube->enemy.state = PURSUIT;
			ray->hit = 1;
			return ;
		}
	}
	cube->enemy.state = WANDER;
}

void	find_player(t_cube *cube, t_player *monster, t_player *player)
{
	t_ray	ray;
	double	dis_sq;

	ft_memset(&ray, 0, sizeof(t_ray));
	ray.ray_dir_x = player->x - monster->x;
	ray.ray_dir_y = player->y - monster->y;
	dis_sq = pow(ray.ray_dir_x, 2.0) + pow(ray.ray_dir_y, 2.0);
	if (sqrt(dis_sq) > 5.0)
		return ;
	ray.ray_dir_x /= sqrt(dis_sq);
	ray.ray_dir_y /= sqrt(dis_sq);
	init_dda(monster, &ray);
	init_steps(monster, &ray);
	dda_monster_loop(&ray, cube, sqrt(dis_sq));
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
	find_player(cube, &cube->enemy.monster, &cube->player);
	if (cube->enemy.state == WANDER)
	{
		cube->enemy.speed = 0.5;
		cube->enemy.anim_speed = 0.09;
		enemy_wander(cube, &cube->enemy);
	}
	else if (cube->enemy.state == PURSUIT)
	{
		cube->enemy.speed = 1.0;
		cube->enemy.anim_speed = 0.03;
		enemy_chase(cube, &cube->enemy);
	}
}
