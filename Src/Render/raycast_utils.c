/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:44:16 by andcarva          #+#    #+#             */
/*   Updated: 2025/09/24 15:44:17 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (ray->map_x < 0 || ray->map_x >= map_width || \
ray->map_y < 0 || ray->map_y >= map_height)
	{
		ray->hit = 1;
		return (1);
	}
	return (0);
}

void	wall_light(t_cube *cube, t_ray *ray, double *factor)
{
	if (ray->perp_wall_dist <= cube->light.radius)
		*factor = cube->light.min + (cube->light.max - cube->light.min) \
* (1.0 - ray->perp_wall_dist / cube->light.radius);
	else
		*factor = cube->light.min;
}
