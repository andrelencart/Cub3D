
#include "../../Inc/cube3d.h"


void	draw(t_cube *cube)
{
	ft_memset(cube->window.addr, 0, WIND_WIDTH * WIND_HEIGHT * (cube->window.bitpp / 8));
	// mlx_destroy_image(cube->window.mlx, cube->window.img);
	// cube->window.img = mlx_new_image(cube->window.mlx, WIND_WIDTH, WIND_HEIGHT);
	// mlx_clear_window(cube->window.mlx, cube->window.mlx_window);
	raycast(cube);
	draw_mini_map(cube);
	mlx_put_image_to_window(cube->window.mlx,cube->window.mlx_window, cube->window.img, 0, 0);
}

void	raycast(t_cube *cube)
{
	t_ray	ray;
	int		x;
	// int		map_height;

	// map_height = cube->map.height;
	x = 0;
	while (x < WIND_WIDTH)
	{
		ft_memset(&ray, 0, sizeof(ray));
		init_ray(&cube->player, &ray, x);
		init_dda(&cube->player, &ray);
		init_steps(&cube->player, &ray);
		dda_loop(&ray, cube->map.grid, cube->map.height, cube->map.width);
		calc_wall_dist(&cube->player, &ray);
		// printf("Ray %d: dir_x=%.2f, dir_y=%.2f, map_x=%d, map_y=%d, step_x=%d, step_y=%d\n",
				// x, ray.ray_dir_x, ray.ray_dir_y, ray.map_x, ray.map_y, ray.step_x, ray.step_y);
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
	while (y < ray->draw_start) // CEILING
	{
		my_mlx_pixel_put(win, x, y, dim_color(CEILING_COLOR_DK_G, DIM_FACTOR));
		y++;
	}
	while (y <= ray->draw_end && y < WIND_HEIGHT) // WALL
	{
		my_mlx_pixel_put(win, x, y, dim_color(WALL_COLOR_MG, DIM_FACTOR));
		y++;
	}
	while (y < WIND_HEIGHT) // FLOOR
	{
		my_mlx_pixel_put(win, x, y, dim_color(FLOOR_COLOR_LGHT_G, DIM_FACTOR));
		y++;
	}
}
