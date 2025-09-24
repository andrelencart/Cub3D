/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:42:48 by andcarva          #+#    #+#             */
/*   Updated: 2025/09/24 15:42:49 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/cube3d.h"

int	get_tile_color(char c, t_cube *cube)
{
	(void)cube;
	if (c == '1' || c == ' ')
		return (dim_color(CEILING_COLOR_DK_G, 0.5));
	if (c == '0' || c == 'P' || c == 'O' \
|| c == 'F')
		return (dim_color(WALL_COLOR_MG, 0.5));
	if (c == 'D')
		return (dim_color(DOOR_COLOR, 0.5));
	if (c == 'X')
		return (dim_color(EXIT_COLOR, 0.5));
	return (WHITE);
}

void	draw_tile(t_cube *cube, int start_x, int start_y, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			my_mlx_pixel_put(&cube->game_img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	set_player_camera_plane(t_player *player)
{
	double	fov;

	fov = 0.66;
	player->plane_x = -player->dir_y * fov;
	player->plane_y = player->dir_x * fov;
}

void	calc_wall_x(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}
