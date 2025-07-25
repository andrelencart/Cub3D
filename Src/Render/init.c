

#include "../../Inc/cube3d.h"

void	init(t_cube *cube)
{
	init_window(&cube->window);
	init_player(&cube->player);
	init_map(&cube->map);
}

void	init_player(t_player *player)
{
	player->x = 4.5; // Position
	player->y = 4.5;
	player->dir_x = -1.0; // where is facing
	player->dir_y = -1.0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->rot_speed = 0.05; // For the Field Of View, 0.66 comonly used for the type of game
}

void	init_map(t_map *map)
{
	map->grid = test_map;
	map->width = strlen(test_map[0]);
	map->height = 0;
	while (map->grid[map->height])
        map->height++;
}

void	init_window(t_window *window)
{
	window->mlx = mlx_init();
	window->mlx_window = mlx_new_window(window->mlx, WIND_WIDTH, \
		WIND_HEIGHT, "CUBE3D");
	window->img = mlx_new_image(window->mlx, WIND_WIDTH, WIND_HEIGHT);
	window->addr = mlx_get_data_addr(window->img, &window->bitpp, \
		&window->line_length, &window->endian);
}

int	close_window(t_window *window)
{
	mlx_destroy_image(window->mlx, window->img);
	mlx_destroy_window(window->mlx, window->mlx_window);
	mlx_destroy_display(window->mlx);
	free(window->mlx);
	exit(0);
}