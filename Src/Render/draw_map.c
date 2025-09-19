#include "../../Inc/cube3d.h"

void	draw(t_cube *cube)
{
// 	ft_memset(cube->window.addr, 0, WIND_WIDTH * WIND_HEIGHT * (cube->window.bitpp / 8));
	raycast(cube);
	draw_monster(&cube->enemy, cube);
	draw_mini_map(cube);
	mlx_put_image_to_window(cube->window.mlx, \
cube->window.mlx_window, cube->game_img.img, 0, 0);
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
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(&cube->game_img, x, y, \
dim_color(cube->imgsmap.ceiling, cube->light.min));
		y++;
	}
	walls(cube, ray, x, &y);
}

void	walls(t_cube *cube, t_ray *ray, int x, int *y)
{
	double	floor[2];
	double	factor;
	int		color;
	t_door	*door;

	factor = 0.0;
	while (*y <= ray->draw_end && *y < WIND_HEIGHT)
	{
		wall_light(cube, ray, &factor);
		if (ray->hit_door)
		{
			door = find_door(&cube->map, ray->map_x, ray->map_y);
			if (door && door->state < 1.0)
				color = get_texture_color(cube, ray, *y);
		}
		else
			color = get_texture_color(cube, ray, *y);
		my_mlx_pixel_put(&cube->game_img, x, *y, dim_color(color, factor));
		(*y)++;
	}
	floors(cube, floor, x, y);
}

void	floors(t_cube *cube, double floor[2], int x, int *y)
{
	double	row_distance;
	double	factor;

	factor = 0.0;
	while (*y < WIND_HEIGHT)
	{
		get_row_distance_and_rays(cube, *y, &row_distance);
		compute_floor_pos(x, row_distance, cube, floor);
		factor = get_light_factor(floor[0], floor[1], \
&cube->player, &cube->light);
		my_mlx_pixel_put(&cube->game_img, x, *y, \
dim_color(cube->imgsmap.floor, factor));
		(*y)++;
	}
}
