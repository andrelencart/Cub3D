

#include "../../Inc/cube3d.h"

void	my_mlx_pixel_put(t_window *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bitpp / 8));
	*(unsigned int *)dst = color;
}