
#include "../../Inc/cube3d.h"

void	draw_mini_map(t_cube *cube, int half_view)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	cube->mini_map.offset_x = 20;
	cube->mini_map.offset_y = 20;
	y = -half_view;
	while (y <= half_view)
	{
		map_y = (int)(cube->player.y) + y;
		x = -half_view;
		while (x < cube->map.width)
		{
			map_x = (int)(cube->player.x) + x;
			get_mini_map_color(cube, map_x, map_y, half_view);
			// draw_tile(&cube->window, cube->mini_map.offset_x + x * TILE_SIZE, cube->mini_map.offset_y + y * TILE_SIZE,
			// get_tile_color(cube->map.grid[y][x]));
			x++;
		}
		y++;
	}
	draw_vision_mini_map(cube);
	draw_player_mini_map(cube);
}

void	draw_player_mini_map(t_cube *cube)
{
	int	x;
	int	y;

	cube->mini_map.player_mini_x = (int)((cube->player.x + 0.5) * TILE_SIZE);
	cube->mini_map.player_mini_y = (int)((cube->player.y) * TILE_SIZE);
	cube->mini_map.player_size = TILE_SIZE / 4;
	y = -cube->mini_map.player_size;
	while (y <= cube->mini_map.player_size)
	{
		x = -cube->mini_map.player_size;
		while (x <= cube->mini_map.player_size)
		{
			my_mlx_pixel_put(&cube->window, cube->mini_map.player_mini_x + x, \
			cube->mini_map.player_mini_y + y, RED);
			x++;
		}
		y++;
	}
}

void	draw_vision_mini_map(t_cube *cube)
{
	int		draw_x;
	int		draw_y;
	int		x;
	int		y;

	draw_x = 0;
	draw_y = 0;
	cube->mini_map.player_mini_x = (int)((cube->player.x + 0.5) * TILE_SIZE);
	cube->mini_map.player_mini_y = (int)((cube->player.y) * TILE_SIZE);
	y = 0;
	while (y < cube->mini_map.num_rays)
	{
		cube->mini_map.camera_x = - (2 * y / (double)(cube->mini_map.num_rays - 1) - 1);
		cube->mini_map.ray_dir_x = (cube->player.dir_x + cube->player.plane_x * cube->mini_map.camera_x);
		cube->mini_map.ray_dir_y = (cube->player.dir_y + cube->player.plane_y * cube->mini_map.camera_x);
		x = 0;
		while (x < cube->mini_map.ray_length)
		{
			draw_x = (int)(cube->mini_map.player_mini_x + cube->mini_map.ray_dir_x * x);
			draw_y = (int)(cube->mini_map.player_mini_y + cube->mini_map.ray_dir_y * x);
			my_mlx_pixel_put(&cube->window, draw_x, draw_y, RED);
			x++;
		}
		y++;
	}
}
