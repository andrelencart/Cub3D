
#include "../../Inc/cube3d.h"

void	draw_mini_map(t_cube *cube)
{
	int	x;
	int	y;

	// offset_x = (WIND_WIDTH - map->width * TILE_SIZE) / 2;
	// offset_y = (WIND_HEIGHT - map->height * TILE_SIZE) / 2;
	cube->mini_map.offset_x = 0;
	cube->mini_map.offset_y = 0;
	y = 0;
	while (y < cube->map.height)
	{
		x = 0;
		while (x < cube->map.width)
		{
			draw_tile(&cube->window, cube->mini_map.offset_x + x * TILE_SIZE, cube->mini_map.offset_y + y * TILE_SIZE,
			get_tile_color(cube->map.grid[y][x]));
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
	cube->mini_map.player_mini_y = (int)((cube->map.height - cube->player.y) * TILE_SIZE);
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
	cube->mini_map.player_mini_y = (int)((cube->map.height - cube->player.y) * TILE_SIZE);
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
			draw_y = (int)(cube->mini_map.player_mini_y - cube->mini_map.ray_dir_y * x);
			my_mlx_pixel_put(&cube->window, draw_x, draw_y, RED);
			x++;
		}
		y++;
	}
}
