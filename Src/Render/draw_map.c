
#include "../../Inc/cube3d.h"


void	draw(t_cube *cube)
{
	draw_map(&cube->window, &cube->map);
	mlx_put_image_to_window(cube->window.mlx,cube->window.mlx_window, cube->window.img, 0, 0);
}

void	draw_tile(t_window *win, int start_x, int start_y, int color)
{
	int	y;
	int	x;
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			my_mlx_pixel_put(win, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_window *win, t_map *map)
{
	int	x;
	int	y;
	int color = 0;
    while (map->grid[map->height])
        map->height++;
    int offset_x = (WIND_WIDTH - map->width * TILE_SIZE) / 2;
    int offset_y = (WIND_HEIGHT - map->height * TILE_SIZE) / 2;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
            if (map->grid[y][x] == '1')
                color = CEILING_COLOR;
            else if (map->grid[y][x] == '0')
                color = FLOOR_COLOR;
            else if (map->grid[y][x] == 'P')
                color = RED;
            else
                color = WHITE;
            draw_tile(win, offset_x + x * TILE_SIZE, offset_y + y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
}
