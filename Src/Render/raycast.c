
#include "../../Inc/cube3d.h"

void	init_ray(t_player *player, t_ray *ray, int x)
{
	// Map the current screen column x to a value from -1 (left) to +1 (right).
	ray->camera_x = 2 * x / (double)WIND_WIDTH - 1;

	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
}

void	init_dda(t_player *player, t_ray *ray)
{
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	init_steps(t_player *player, t_ray *ray)
{
	// direction and initial distance of the Ray for the X
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}

	// direction and initial distance of the Ray for the Y
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

void	dda_loop(t_ray *ray, char **map, int map_height, int map_width)
{
	ray->hit = 0;
	ray->hit_door = 0;
	while (ray->hit == 0)
	{
		if (raycast_wall_hit(ray, map_height, map_width) == 1)
			break;
		if (map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
		else if (map[ray->map_y][ray->map_x] == 'D')
		{
			ray->hit = 1;
			ray->hit_door = 1;
		}
	}
}

void	calc_wall_dist(t_player *player, t_ray *ray)
{
	//perpendicular distance from the player to the wall that the ray hits
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(WIND_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = (WIND_HEIGHT / 2) - (ray->line_height / 2); // Find the lowest pixel to start drawing the wall
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIND_HEIGHT / 2; // Find the highest pixel to end drawing the wall
	if (ray->draw_end >= WIND_HEIGHT)
		ray->draw_end = WIND_HEIGHT - 1;
}