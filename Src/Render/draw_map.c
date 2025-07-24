
#include "../../Inc/cube3d.h"


void	draw(t_cube *cube)
{
	raycast(cube);
	draw_mini_map(&cube->window, &cube->map);
	mlx_put_image_to_window(cube->window.mlx,cube->window.mlx_window, cube->window.img, 0, 0);
}

void	raycast(t_cube *cube)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIND_WIDTH)
	{
		init_ray(&cube->player, &ray, x);
		init_dda(&cube->player, &ray);
		init_steps(&cube->player, &ray);
		dda_loop(&ray, cube->map.grid);
		// printf("Ray %d: dir_x=%.2f, dir_y=%.2f, map_x=%d, map_y=%d, step_x=%d, step_y=%d\n",
		// 		x, ray.ray_dir_x, ray.ray_dir_y, ray.map_x, ray.map_y, ray.step_x, ray.step_y);
		calc_wall_dist(&cube->player, &ray);
		draw_3d_map(&cube->window, &ray, x);
		x++;
	}
}

void	draw_3d_map(t_window *win, t_ray *ray, int x)
{
	int	y;

	y = ray->draw_start;
	if (y < 0)
		y = 0;
	while (y <= ray->draw_start) // CEILING
	{
		my_mlx_pixel_put(win, x, y, CEILING_COLOR_DK_G);
		y++;
	}
	while (y <= ray->draw_end && y < WIND_HEIGHT) // WALL
	{
		my_mlx_pixel_put(win, x, y, WALL_COLOR_MG);
		y++;
	}
	while (y < WIND_HEIGHT) // FLOOR
	{
		my_mlx_pixel_put(win, x, y, FLOOR_COLOR_LGHT_G);
		y++;
	}
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

void	draw_mini_map(t_window *win, t_map *map)
{
	int	x;
	int	y;
	int	offset_x;
	int	offset_y;

	// offset_x = (WIND_WIDTH - map->width * TILE_SIZE) / 2;
	// offset_y = (WIND_HEIGHT - map->height * TILE_SIZE) / 2;
	offset_x = 0;
	offset_y = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			draw_tile(win, offset_x + x * TILE_SIZE, offset_y + y * TILE_SIZE, \
			get_tile_color(map->grid[y][x]));
			x++;
		}
		y++;
	}
}

