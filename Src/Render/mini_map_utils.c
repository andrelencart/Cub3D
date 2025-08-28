
#include "../../Inc/cube3d.h"

void	get_mini_map_color(t_cube *cube, int x, int y, int half_view)
{
	int map_x;
	int map_y;
	int	pixel_x;
	int	pixel_y;

	map_x = (int)(cube->player.x) + x;
	map_y = (int)(cube->player.y) + y;
	pixel_x = (x + half_view - (cube->player.x - (int)cube->player.x)) * MINIMAP_TILE_SIZE;
	pixel_y = (y + half_view - (cube->player.y - (int)cube->player.y)) * MINIMAP_TILE_SIZE;
	cube->mini_map.color = CEILING_COLOR_DK_G;
	if (map_x >= 0 && map_x < cube->map.width && map_y >= 0 && map_y < cube->map.height)
		cube->mini_map.color = get_tile_color(cube->map.grid[map_y][map_x], cube);
	draw_tile(&cube->window, pixel_x, pixel_y, cube->mini_map.color);
}
