
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
		calc_wall_x(&cube->ray, &cube->player);
		draw_3d_map(cube, &ray, x);
		x++;
	}
}

void	draw_3d_map(t_cube *cube, t_ray *ray, int x)
{
	int		y;

	y = ray->draw_start;
	if (y < 0)
		y = 0;
	while (y < ray->draw_start) // CEILING
	{
		my_mlx_pixel_put(&cube->window, x, y, dim_color(CEILING_COLOR_DK_G, cube->light.min));
		y++;
	}
	floors_walls(cube, ray, x, &y);
}

void	floors_walls(t_cube *cube, t_ray *ray, int x, int *y)
{
	// double	hit[2];
	double	floor[2];
	double	factor;

	while (*y <= ray->draw_end && *y < WIND_HEIGHT)
	{
		// get_wall_pixel_pos(ray, cube, *y, hit);
		// factor = get_light_factor(hit[0], hit[1], &cube->player, &cube->light);
		// my_mlx_pixel_put(&cube->window, x, *y, dim_color(WALL_COLOR_MG, factor));
		if (ray->perp_wall_dist <= cube->light.radius)
			factor = cube->light.min + (cube->light.max - cube->light.min) * (1.0 - ray->perp_wall_dist / cube->light.radius);
		else
			factor = cube->light.min;
		my_mlx_pixel_put(&cube->window, x, *y, dim_color(WALL_COLOR_MG, factor));
		(*y)++;
	}
	while (*y < WIND_HEIGHT)
	{
		get_floor_pixel_pos(ray, cube, *y, floor);
		factor = get_light_factor(floor[0], floor[1], &cube->player, &cube->light);
		// printf("floor_x: %f, floor_y: %f, factor: %f\n", floor_x, floor_y, factor);
		// factor *= 0.5;
		my_mlx_pixel_put(&cube->window, x, *y, dim_color(RED, factor));
		(*y)++;
	}
}
