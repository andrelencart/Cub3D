
#include "../../Inc/cube3d.h"

int	is_wall(t_cube *cube, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || mx >= cube->map.width || my < 0 || my >= cube->map.height)
		return (1);
	return(cube->map.grid[my][mx] == '1' || cube->map.grid[my][mx] == 'D');
}

int	can_move(t_cube *cube, double x, double y, double radius)
{
	if (is_wall(cube, x - radius, y - radius))
		return (0);
	if (is_wall(cube, x + radius, y - radius))
		return (0);
	if (is_wall(cube, x - radius, y + radius))
		return (0);
	if (is_wall(cube, x + radius, y + radius))
		return (0);
	return (1);
}

void print_map(t_map *map)
{
    int y, x;
    for (y = 0; y < map->height; y++)
    {
        for (x = 0; x < map->width; x++)
        {
            printf("%c", map->grid[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}