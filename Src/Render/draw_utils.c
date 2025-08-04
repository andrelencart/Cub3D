
#include "../../Inc/cube3d.h"

int	get_tile_color(char c)
{
	if (c == '1')
		return (CEILING_COLOR_DK_G);
	if (c == '0' || c == 'P')
		return (FLOOR_COLOR_LGHT_G);
	// if (c == 'P')
	// 	return (RED);
	return (WHITE);
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

void	my_mlx_pixel_put(t_window *win, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIND_WIDTH || y < 0 || y >= WIND_HEIGHT)
		return;
	dst = win->addr + (y * win->line_length + x * (win->bitpp / 8));
	*(unsigned int *)dst = color;
}

int	testkey(int key_code, t_window *wind)
{
	(void)wind;
	ft_printf("key_code: %d\n", key_code);
	return (0);
}
