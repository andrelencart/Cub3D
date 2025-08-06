

#include "../../Inc/cube3d.h"
/* 
static char *test_map[] = {
	"1111111111",
    "1000000001",
    "1011111101",
    "1010000101",
    "1010P00101",
    "1010111101",
    "1000000001",
    "1111111111",
    NULL
};
 */
void	init(t_cube *cube, t_parse *data)
{
	init_window(&cube->window);
	init_player(&cube->player, data);
	init_map(&cube->map, data);
	init_mini_map(&cube->mini_map);
}

void	init_player(t_player *player, t_parse *data)
{
	player->x = data->player_x + 0.5; // x Position
	player->y = data->player_y + 0.5; // y Position
	player->dir_x = data->player_dir_x;//assumed E is x -1.0
	player->dir_y = data->player_dir_y;//assumed N is y -1.0
	// player->plane_x = 0;
	// player->plane_y = 0.66;
	set_player_camera_plane(player);
	player->rot_speed = 0.05; // For the Field Of View, 0.66 comonly used for the type of game
	player->moving_forward = 0;
	player->moving_backward = 0;
	player->strafing_left = 0;
	player->strafing_right = 0;
}

void	init_map(t_map *map, t_parse *data)
{
	map->grid = data->map;
	map->width = strlen(map->grid[0]);
	map->height = 0;
	while (map->grid[map->height])
		map->height++;
}

void	init_mini_map(t_mini_map *mini_map)
{
	mini_map->offset_x = 0;
	mini_map->offset_y = 0;
	mini_map->tile_size = TILE_SIZE;
	mini_map->num_rays = 20;
	mini_map->ray_length = TILE_SIZE * 3;
	mini_map->player_mini_x = 0;
	mini_map->player_mini_y = 0;
	mini_map->player_size = 0;
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