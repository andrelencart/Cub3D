
#include "../../Inc/cube3d.h"

void	get_mini_map_color(t_cube *cube, int map_x, int map_y, int half_view)
{
	int	color;

	color = BLACK;
	if (map_x >= 0 && map_x < cube->map.width && map_y >= 0 && map_y < cube->map.height)
		color = get_tile_color(cube->map.grid[map_y][map_x]);
	draw_tile(&cube->window,
		cube->mini_map.offset_x + ((int)(cube->player.x) + half_view) * MINIMAP_TILE_SIZE,
		cube->mini_map.offset_y + ((int)(cube->player.y) + half_view) * MINIMAP_TILE_SIZE,
		color);
}
