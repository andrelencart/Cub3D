#include "../../Inc/cube3d.h"

void	my_mlx_pixel_put(t_image *win, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIND_WIDTH || y < 0 || y >= WIND_HEIGHT)
		return ;
	dst = win->addr + (y * win->line_length + x * (win->bitpp / 8));
	*(unsigned int *)dst = color;
}

int	testkey(int key_code, t_window *wind)
{
	(void)wind;
	ft_printf("key_code: %d\n", key_code);
	return (0);
}

// void print_map(t_map *map)
// {
//     int y, x;
//     for (y = 0; y < map->height; y++)
//     {
//         for (x = 0; x < map->width; x++)
//         {
//             printf("%c", map->grid[y][x]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }