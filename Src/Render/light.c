
#include "../../Inc/cube3d.h"

void init_lighting(t_light *light)
{
	light->radius = LIGHT_RAD;
	light->min = DIM_FACTOR;
	light->max = 2.0;
	light->player_angle = 0.0;
	light->start_angle = 0.0;
	light->end_angle = 0.0;
}

unsigned int dim_color(unsigned int color, double factor)
{
	// Extract red, green, blue from the color integer
	unsigned char r = (color >> 16) & 0xFF;	// Get red
	unsigned char g = (color >> 8) & 0xFF; 	// Get green
	unsigned char b = color & 0xFF;			// Get blue

	if (factor < 0.0)
		factor = 0.0;
	if (factor > 1.0)
		factor = 1.0;

	r = (unsigned char)(r * factor);
	g = (unsigned char)(g * factor);
	b = (unsigned char)(b * factor);

	// Combine back to integer
	return (r << 16) | (g << 8) | b;
}

// double get_vertical_light_factor(int y, int draw_end, int window_height, double min, double max)
// {
// 	double t;

// 	t = (double)(y - draw_end) / (window_height - draw_end);
// 	if (t < 0.0)
// 		t = 0.0;
// 	if (t > 1.0)
// 		t = 1.0;
// 	t = sqrt(t);
// 	return (min + (max - min) * (1.0 - t));
// }

double get_light_factor(double px, double py, t_player *player, t_light *light)
{
	double d[2];
	double dist;
	double factor;

	d[0] = px - player->x;
	d[1] = py - player->y;
	dist = sqrt(d[0] * d[0] + d[1] * d[1]);
	if (dist <= light->radius)
		factor = light->min + (light->max - light->min) * (1.0 - dist / light->radius);
	else
		factor = light->min;
	return (factor);
}

// void get_floor_pixel_pos(t_ray *ray, t_cube *cube, int y, double floor[2])
// {
// 	double	row_distance;
// 	double	floor_wall_x;
// 	double	floor_wall_y;
// 	double	weight;

// 	row_distance = (double)WIND_HEIGHT / (2.0 * y - WIND_HEIGHT);
// 	if (ray->side == 0)
// 	{
// 		floor_wall_x = ray->map_x + ray->wall_x;
// 		floor_wall_y = ray->map_y;
// 	}
// 	else
// 	{
// 		floor_wall_x = ray->map_x;
// 		floor_wall_y = ray->map_y + ray->wall_x;
// 	}
// 	weight = row_distance / ray->perp_wall_dist;
// 	floor[0] = weight * floor_wall_x + (1.0 - weight) * cube->player.x;
// 	floor[1] = weight * floor_wall_y + (1.0 - weight) * cube->player.y;
// }

// void get_floor_pixel_pos(int x, int y, t_cube *cube, double floor[2])
// {
// 	double rayDirX0 = cube->player.dir_x - cube->player.plane_x;
// 	double rayDirY0 = cube->player.dir_y - cube->player.plane_y;
// 	double rayDirX1 = cube->player.dir_x + cube->player.plane_x;
// 	double rayDirY1 = cube->player.dir_y + cube->player.plane_y;

// 	// Row (distance from player to floor for this y)
// 	int p = y - (WIND_HEIGHT / 2);
// 	double posZ = 0.5 * WIND_HEIGHT;
// 	double rowDistance = posZ / p;

// 	// Interpolate across the screen
// 	double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIND_WIDTH;
// 	double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIND_WIDTH;
// 	double floorX = cube->player.x + rowDistance * rayDirX0 + x * floorStepX;
// 	double floorY = cube->player.y + rowDistance * rayDirY0 + x * floorStepY;
// 	floor[0] = floorX;
// 	floor[1] = floorY;
// }

void	get_row_distance_and_rays(t_cube *cube, int y, double *row_distance)
{
	int		p;
	double	posZ;

	posZ = 0.5 * WIND_HEIGHT;
	p = y - (WIND_HEIGHT / 2);
	*row_distance = posZ / p;
	cube->ray.raydir_light[0] = cube->player.dir_x - cube->player.plane_x;
	cube->ray.raydir_light[1] = cube->player.dir_y - cube->player.plane_y;
	cube->ray.raydir_light[2] = cube->player.dir_x + cube->player.plane_x;
	cube->ray.raydir_light[3] = cube->player.dir_y + cube->player.plane_y;
}

void	compute_floor_pos(int x, double row_distance, t_cube *cube, double floor[2])
{
	double	floorStepX;
	double	floorStepY;

	floorStepX = row_distance * (cube->ray.raydir_light[2] - cube->ray.raydir_light[0]) / WIND_WIDTH;
	floorStepY = row_distance * (cube->ray.raydir_light[3] - cube->ray.raydir_light[1]) / WIND_WIDTH;
	floor[0] = cube->player.x + row_distance * cube->ray.raydir_light[0] + x * floorStepX;
	floor[1] = cube->player.y + row_distance * cube->ray.raydir_light[1] + x * floorStepY;
}

