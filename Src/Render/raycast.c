
#include "../../Inc/cube3d.h"

void	init_ray(t_player *player, t_ray *ray, int x)
{
	// Map the current screen column x to a value from -1 (left) to +1 (right).
	ray->camera_x = 2 * x / (double)WIND_WIDTH - 1;

	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x; 
	ray->ray_dir_x = player->dir_y + player->plane_y * ray->camera_x; 
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
	// Step direction and initial side distance for X
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

	// Step direction and initial side distance for Y
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

void	raycast(t_cube *cube)
{
	int		x;
	t_ray ray;

	x = 0;
	while (x < WIND_WIDTH)
	{
		init_ray(&cube->player, &ray, x);
		init_dda(&cube->player, &ray);
		init_steps(&cube->player, &ray);
		// perform_dda(&map, &ray);
		// calc_wall_dist(&cube->player, &ray);
		// draw_wall(&cube->window, &ray, x);
		// x++;
	}
}