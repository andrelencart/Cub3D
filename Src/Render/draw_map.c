#include "../../Inc/cube3d.h"

void	draw(t_cube *cube)
{
	// mlx_mouse_hide(cube->window.mlx, cube->window.mlx_window);
	ft_memset(cube->window.addr, 0, WIND_WIDTH * WIND_HEIGHT * (cube->window.bitpp / 8));
	// mlx_destroy_image(cube->window.mlx, cube->window.img);
	// cube->window.img = mlx_new_image(cube->window.mlx, WIND_WIDTH, WIND_HEIGHT);
	// mlx_clear_window(cube->window.mlx, cube->window.mlx_window);
	raycast(cube);
	draw_monster(&cube->enemy, cube);
	draw_mini_map(cube);
	mlx_put_image_to_window(cube->window.mlx,cube->window.mlx_window, cube->window.img, 0, 0);
}

void	raycast(t_cube *cube)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIND_WIDTH)
	{
		ft_memset(&ray, 0, sizeof(ray));
		init_ray(&cube->player, &ray, x);
		init_dda(&cube->player, &ray);
		init_steps(&cube->player, &ray);
		dda_loop(&ray, cube->map.grid, cube->map.height, cube->map.width);
		calc_wall_dist(&cube->player, &ray);
		calc_wall_x(&ray, &cube->player);
		draw_3d_map(cube, &ray, x);
		cube->zbuffer[x] = ray.perp_wall_dist;
		x++;
	}
}

void	draw_3d_map(t_cube *cube, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start) // CEILING
	{
		my_mlx_pixel_put(&cube->window, x, y, dim_color(cube->imgsmap.ceiling, cube->light.min));
		y++;
	}
	floors_walls(cube, ray, x, &y);
}

void	floors_walls(t_cube *cube, t_ray *ray, int x, int *y)
{
	double	floor[2];
	double	row_distance;
	double	factor;
	int		color;

	factor = 0.0;
	while (*y <= ray->draw_end && *y < WIND_HEIGHT)
	{
		wall_light(cube, ray, &factor);
		if (ray->hit_door)
		{
			if (cube->map.door.state < 1.0)
				color = DOOR_COLOR;
		}
		else
			color = get_texture_color(cube, ray, *y);
		my_mlx_pixel_put(&cube->window, x, *y, dim_color(color, factor));
		(*y)++;
	}
	while (*y < WIND_HEIGHT)
	{
		get_row_distance_and_rays(cube, *y, &row_distance);
		compute_floor_pos(x, row_distance, cube, floor);
		factor = get_light_factor(floor[0], floor[1], &cube->player, &cube->light);
		my_mlx_pixel_put(&cube->window, x, *y, dim_color(cube->imgsmap.floor, factor));
		(*y)++;
	}
}
