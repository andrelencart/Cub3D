
#include "../../Inc/cube3d.h"

void	init_door(t_door *door)
{
	door->cord_x = 0;
	door->cord_y = 0;
	door->anim_state = 0;
	door->state = 0;
}

void	update_door_animation(t_map *map)
{
	if (map->door.anim_state == -1)
	{
		map->door.state += DOOR_SPEED;
		if (map->door.state >= 1.0)
		{
			map->door.state = 1.0;
			map->door.anim_state = 0;
			map->grid[map->door.cord_y][map->door.cord_x] = 'O';
		}
	}
	if (map->door.anim_state == 1)
	{
		map->door.state -= DOOR_SPEED;
		if (map->door.state <= 0.0)
		{
			map->door.state = 0.0;
			map->door.anim_state = 0;
			map->grid[map->door.cord_y][map->door.cord_x] = 'D';
		}
	}
}

void	door_interaction(t_map *map, t_player *player)
{
	int	front_x;
	int	front_y;

	front_x = (int)(player->x + player->dir_x * PLAYER_INTERACTION);
	front_y = (int)(player->y + player->dir_y * PLAYER_INTERACTION);
	if (front_x <= 0 || front_y <= 0 || front_x >= map->width || front_y >= map->height \
|| map->grid[(int)player->y][(int)player->x] == 'O')
		return ;
	if (map->grid[front_y][front_x] == 'D' || map->grid[front_y][front_x] == 'O')
	{
		if (map->door.anim_state == 0)
		{
			if (map->door.state < 1)
				map->door.anim_state = -1;
			else
				map->door.anim_state = 1;
		}
		map->door.cord_x = front_x;
		map->door.cord_y = front_y;
	}
}


