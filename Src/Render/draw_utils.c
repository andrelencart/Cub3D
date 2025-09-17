#include "../../Inc/cube3d.h"

int	get_tile_color(char c, t_cube *cube)
{
	(void)cube;
	if (c == '1' || c == ' ')
		return (CEILING_COLOR_DK_G);
	if (c == '0' || c == 'P' || c == 'O')
		return (WALL_COLOR_MG);
	if (c == 'D')
		return (DOOR_COLOR);
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
