
#include "../../Inc/cube3d.h"

int	is_wall(t_cube *cube, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || mx >= cube->map.width || my < 0 || my >= cube->map.height)
		return (1);
	return(cube->map.grid[my][mx] == '1');
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
