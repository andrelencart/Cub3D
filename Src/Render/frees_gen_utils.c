#include "../../Inc/cube3d.h"

void	state_of_animation(t_map *map, t_door *door)
{
	if (door->anim_state == -1)
	{
		door->state += DOOR_SPEED;
		if (door->state >= 1.0)
		{
			door->state = 1.0;
			door->anim_state = 0;
			map->grid[door->cord_y][door->cord_x] = 'O';
		}
	}
	if (door->anim_state == 1)
	{
		door->state -= DOOR_SPEED;
		if (door->state <= 0.0)
		{
			door->state = 0.0;
			door->anim_state = 0;
			map->grid[door->cord_y][door->cord_x] = 'D';
		}
	}
}

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
