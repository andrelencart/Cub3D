
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
			my_mlx_pixel_put(win, start_x + x, start_y + y, dim_color(color, DIM_FACTOR));
			x++;
		}
		y++;
	}
}

void set_player_camera_plane(t_player *player)
{
	double fov = 0.66;

	player->plane_x = -player->dir_y * fov;
	player->plane_y = player->dir_x * fov;
}


void	calc_wall_x(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x); // Keep only the fractional part [0,1)
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

