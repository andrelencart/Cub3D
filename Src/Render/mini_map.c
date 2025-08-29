
#include "../../Inc/cube3d.h"

void	draw_mini_map(t_cube *cube)
{
	draw_centered_mini_map(cube, MINIMAP_VIEW_SIZE / 2);
	vision_mini_map(cube, MINIMAP_VIEW_SIZE / 2);
	draw_player_mini_map(cube, MINIMAP_VIEW_SIZE / 2);
}

void	draw_centered_mini_map(t_cube *cube, int half_view)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	cube->mini_map.offset_x = 0;
	cube->mini_map.offset_y = 0;
	y = -half_view;
	while (y <= half_view)
	{
		map_y = (int)(cube->player.y) + y;
		x = -half_view;
		while (x <= half_view)
		{
			map_x = (int)(cube->player.x) + x;
			get_mini_map_color(cube, x, y, half_view);
			// draw_tile(&cube->window, cube->mini_map.offset_x + x * TILE_SIZE, cube->mini_map.offset_y + y * TILE_SIZE,
			// get_tile_color(cube->map.grid[y][x]));
			x++;
		}
		y++;
	}
}
void	draw_player_mini_map(t_cube *cube, int half_view)
{
	int	x;
	int	y;

	cube->mini_map.player_mini_x = cube->mini_map.offset_x + half_view * MINIMAP_TILE_SIZE;
	cube->mini_map.player_mini_y = cube->mini_map.offset_y + half_view * MINIMAP_TILE_SIZE;
	cube->mini_map.player_size = MINIMAP_TILE_SIZE / 3;
	y = -cube->mini_map.player_size;
	while (y <= cube->mini_map.player_size)
	{
		x = -cube->mini_map.player_size;
		while (x <= cube->mini_map.player_size)
		{
			my_mlx_pixel_put(&cube->window, cube->mini_map.player_mini_x + x, \
			cube->mini_map.player_mini_y + y, cube->imgsmap.floor);
			x++;
		}
		y++;
	}
}

void	vision_mini_map(t_cube *cube, int half_view)
{
	int		draw_x;
	int		draw_y;
	int		ray;
	double	angle;

	draw_x = 0;
	draw_y = 0;
	ray = 0;
	vision_mini_map_init(cube, half_view);
	while (ray < cube->mini_map.num_rays)
	{
		// cube->mini_map.camera_x = - (2 * ray / (double)(cube->mini_map.num_rays - 1) - 1);
		// cube->mini_map.ray_dir_x = (cube->player.dir_x + cube->player.plane_x * cube->mini_map.camera_x);
		// cube->mini_map.ray_dir_y = (cube->player.dir_y + cube->player.plane_y * cube->mini_map.camera_x);
		angle = cube->mini_map.light.start_angle + ray * (cube->mini_map.light.end_angle - cube->mini_map.light.start_angle) / (cube->mini_map.num_rays - 1);
		cube->mini_map.ray_dir_x = cos(angle);
		cube->mini_map.ray_dir_y = sin(angle);
		mini_map_vision_draw(cube, draw_x, draw_y);
		ray++;
	}
}
