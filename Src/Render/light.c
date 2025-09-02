
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
	// Dim each channel
	r = (unsigned char)(r * factor);
	g = (unsigned char)(g * factor);
	b = (unsigned char)(b * factor);

	// Combine back to integer
	return (r << 16) | (g << 8) | b;
}

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

void get_floor_pixel_pos(t_ray *ray, t_cube *cube, int y, double floor[2])
{
	double	row_distance;
	double	floor_wall_x;
	double	floor_wall_y;
	double	weight;

	row_distance = (double)WIND_HEIGHT / (2.0 * y - WIND_HEIGHT);
	if (ray->side == 0)
	{
		floor_wall_x = ray->map_x + ray->wall_x;
		floor_wall_y = ray->map_y;
	}
	else
	{
		floor_wall_x = ray->map_x;
		floor_wall_y = ray->map_y + ray->wall_x;
	}
	weight = row_distance / ray->perp_wall_dist;
	floor[0] = weight * floor_wall_x + (1.0 - weight) * cube->player.x;
	floor[1] = weight * floor_wall_y + (1.0 - weight) * cube->player.y;
}



