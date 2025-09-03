
#include "../../Inc/cube3d.h"

int	raycast_wall_hit(t_ray *ray, int map_height, int map_width)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
	if (ray->map_x < 0 || ray->map_x >= map_width ||
		ray->map_y < 0 || ray->map_y >= map_height)
	{
		ray->hit = 1; // Stop if out of bounds
		return (1);
	}
	return (0);
}