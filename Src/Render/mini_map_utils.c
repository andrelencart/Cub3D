#include "../../Inc/cube3d.h"

void	get_mini_map_color(t_cube *cube, int x, int y, int half_view)
{
	int	map_x;
	int	map_y;
	int	pixel_x;
	int	pixel_y;

	map_x = (int)(cube->player.x) + x;
	map_y = (int)(cube->player.y) + y;
	pixel_x = (x + half_view - (cube->player.x - (int)cube->player.x)) \
* MINIMAP_TILE_SIZE;
	pixel_y = (y + half_view - (cube->player.y - (int)cube->player.y)) \
* MINIMAP_TILE_SIZE;
	cube->mini_map.color = CEILING_COLOR_DK_G;
	if (map_x >= 0 && map_x < cube->map.width && map_y >= 0 \
&& map_y < cube->map.height)
		cube->mini_map.color = get_tile_color \
(cube->map.grid[map_y][map_x], cube);
	draw_tile(cube, pixel_x + cube->mini_map.offset_x, \
pixel_y + cube->mini_map.offset_y, cube->mini_map.color);
}

void	mini_map_vision_draw(t_cube *cube, int draw_x, int draw_y)
{
	double	distance;
	double	step;
	double	ray_x;
	double	ray_y;

	step = 0.05;
	distance = 0.0;
	ray_x = cube->player.x;
	ray_y = cube->player.y;
	while (distance < LIGHT_RAD)
	{
		ray_x = cube->player.x + cube->mini_map.ray_dir_x * distance;
		ray_y = cube->player.y + cube->mini_map.ray_dir_y * distance;
		if (is_wall(cube, ray_x, ray_y))
			break ;
		draw_x = (int)(cube->mini_map.player_mini_x + \
cube->mini_map.ray_dir_x * distance * MINIMAP_TILE_SIZE);
		draw_y = (int)(cube->mini_map.player_mini_y + \
cube->mini_map.ray_dir_y * distance * MINIMAP_TILE_SIZE);
		my_mlx_pixel_put(&cube->game_img, draw_x, draw_y, cube->imgsmap.floor);
		distance += step;
	}
}

void	vision_mini_map_init(t_cube *cube, int half_view)
{
	cube->mini_map.player_mini_x = cube->mini_map.offset_x \
+ half_view * MINIMAP_TILE_SIZE;
	cube->mini_map.player_mini_y = cube->mini_map.offset_x \
+ half_view * MINIMAP_TILE_SIZE;
	cube->mini_map.light.m_m_fov = PI;
	cube->mini_map.light.player_angle = atan2 \
(cube->player.dir_y, cube->player.dir_x);
	cube->mini_map.light.start_angle = cube->mini_map.light.player_angle \
- cube->mini_map.light.m_m_fov / 2;
	cube->mini_map.light.end_angle = cube->mini_map.light.player_angle \
+ cube->mini_map.light.m_m_fov / 2;
}
