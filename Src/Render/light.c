/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:43:31 by andcarva          #+#    #+#             */
/*   Updated: 2025/09/24 15:43:32 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/cube3d.h"

void	init_lighting(t_light *light)
{
	light->radius = LIGHT_RAD;
	light->min = DIM_FACTOR;
	light->max = 2.0;
	light->player_angle = 0.0;
	light->start_angle = 0.0;
	light->end_angle = 0.0;
}

unsigned int	dim_color(unsigned int color, double factor)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (factor < 0.0)
		factor = 0.0;
	if (factor > 1.0)
		factor = 1.0;
	r = (unsigned char)(r * factor);
	g = (unsigned char)(g * factor);
	b = (unsigned char)(b * factor);
	return ((r << 16) | (g << 8) | b);
}

double	get_light_factor(double px, double py, t_player *player, t_light *light)
{
	double	d[2];
	double	dist;
	double	factor;

	d[0] = px - player->x;
	d[1] = py - player->y;
	dist = sqrt(d[0] * d[0] + d[1] * d[1]);
	if (dist <= light->radius)
		factor = light->min + (light->max - light->min) \
* (1.0 - dist / light->radius);
	else
		factor = light->min;
	return (factor);
}

void	get_row_distance_and_rays(t_cube *cube, int y, double *row_distance)
{
	int		p;
	double	posz;

	posz = 0.5 * WIND_HEIGHT;
	p = y - (WIND_HEIGHT / 2);
	*row_distance = posz / p;
	cube->ray.raydir_light[0] = cube->player.dir_x - cube->player.plane_x;
	cube->ray.raydir_light[1] = cube->player.dir_y - cube->player.plane_y;
	cube->ray.raydir_light[2] = cube->player.dir_x + cube->player.plane_x;
	cube->ray.raydir_light[3] = cube->player.dir_y + cube->player.plane_y;
}

void	compute_floor_pos(int x, double row_distance, \
t_cube *cube, double floor[2])
{
	double	floorstepx;
	double	floorstepy;

	floorstepx = row_distance * (cube->ray.raydir_light[2] \
- cube->ray.raydir_light[0]) / WIND_WIDTH;
	floorstepy = row_distance * (cube->ray.raydir_light[3] \
- cube->ray.raydir_light[1]) / WIND_WIDTH;
	floor[0] = cube->player.x + row_distance * cube->ray.raydir_light[0] \
+ x * floorstepx;
	floor[1] = cube->player.y + row_distance * cube->ray.raydir_light[1] \
+ x * floorstepy;
}
