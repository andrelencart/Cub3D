/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:42:32 by andcarva          #+#    #+#             */
/*   Updated: 2025/09/24 15:42:34 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/cube3d.h"

int	init_door(t_map *map)
{
	int	x;
	int	y;
	int	d;

	count_doors(map);
	map->doors = malloc(sizeof(t_door) * map->n_doors);
	if (!map->doors)
		return (1);
	y = 0;
	d = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			init_the_door(map, y, x, &d);
			x++;
		}
		y++;
	}
	return (0);
}

void	count_doors(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	map->n_doors = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'D')
				map->n_doors++;
			x++;
		}
		y++;
	}
}

void	update_door_animation(t_map *map)
{
	int		i;
	t_door	*door;

	i = 0;
	while (i < map->n_doors)
	{
		door = &map->doors[i];
		state_of_animation(map, door);
		i++;
	}
}

t_door	*find_door(t_map *map, int x, int y)
{
	int	i;

	i = 0;
	while (i < map->n_doors)
	{
		if (map->doors[i].cord_x == x && map->doors[i].cord_y == y)
			return (&map->doors[i]);
		i++;
	}
	return (NULL);
}

void	door_interaction(t_map *map, t_player *player)
{
	int		front_x;
	int		front_y;
	t_door	*door;

	front_x = (int)(player->x + player->dir_x * PLAYER_INTERACTION);
	front_y = (int)(player->y + player->dir_y * PLAYER_INTERACTION);
	if (front_x <= 0 || front_y <= 0 || front_x >= map->width \
|| front_y >= map->height || map->grid[(int)player->y][(int)player->x] == 'O')
		return ;
	if (map->grid[front_y][front_x] == 'D' \
|| map->grid[front_y][front_x] == 'O')
	{
		door = find_door(map, front_x, front_y);
		if (door && door->anim_state == 0)
		{
			if (door->state < 1)
				door->anim_state = -1;
			else
				door->anim_state = 1;
		}
	}
}
