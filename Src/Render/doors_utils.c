#include "../../Inc/cube3d.h"

void	state_of_animation(t_map *map, t_door *door)
{
	if (door->anim_state == -1)
	{
		door->state += DOOR_SPEED;
		if (door->state >= 1.0)
		{
			door->state = 1.0;
			door->anim_state = 0;
			map->grid[door->cord_y][door->cord_x] = 'O';
		}
	}
	if (door->anim_state == 1)
	{
		door->state -= DOOR_SPEED;
		if (door->state <= 0.0)
		{
			door->state = 0.0;
			door->anim_state = 0;
			map->grid[door->cord_y][door->cord_x] = 'D';
		}
	}
}

void	init_the_door(t_map *map, int y, int x, int *d)
{
	if (map->grid[y][x] == 'D')
	{
		map->doors[*d].cord_x = x;
		map->doors[*d].cord_y = y;
		map->doors[*d].state = 0.0;
		map->doors[*d].anim_state = 0;
		(*d)++;;
	}
}

void	exit_interaction(t_map *map, t_player *player)
{
	int		front_x;
	int		front_y;

	front_x = (int)(player->x + player->dir_x * PLAYER_INTERACTION);
	front_y = (int)(player->y + player->dir_y * PLAYER_INTERACTION);
	if (front_x <= 0 || front_y <= 0 || front_x >= map->width \
|| front_y >= map->height || map->grid[(int)player->y][(int)player->x] == 'O')
		return ;
	if (map->grid[front_y][front_x] == 'X')
		map->grid[front_y][front_x] = 'F';
}
