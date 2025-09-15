

#include "../../Inc/cube3d.h"

// static char *test_map[] = {
// 	"1111111111",
//     "1000000001",
//     "1011111101",
//     "1010000101",
//     "1010P00101",
//     "1010111101",
//     "1000000001",
//     "1111111111",
//     NULL
// };

void	init(t_cube *cube, t_parse *data)
{
	ft_memset(cube, 0, sizeof(t_cube));
	init_window(&cube->window);
	init_map(&cube->map, data);
	init_player(&cube->player, data, cube->map.height);
	cube->zbuffer = ft_calloc(WIND_WIDTH, sizeof(double));
	if (!cube->zbuffer)
	{
		ft_printf_fd(2, "Failed to allocate zbuffer memory");
		free_data(data);
		close_window(cube);
	}
	if (init_imgsmap(cube->window.mlx, &cube->imgsmap, data))
	{
		free_data(data);
		close_window(cube);
	}
	if (init_monster(cube, data))
	{
		free_data(data);
		close_window(cube);
	}
	init_mini_map(&cube->mini_map);
	init_lighting(&cube->light);
}

void	init_player(t_player *player, t_parse *data, int map_height)
{
	(void)map_height;
	player->x = data->player_x + 0.5; // x Position
	player->y = data->player_y + 0.5; // y Position (INVERTED)
	player->dir_x = data->player_dir_x;
	player->dir_y = data->player_dir_y;
	player->init_pos_x = data->player_dir_x;
	player->init_pos_y = data->player_dir_y;
	set_player_camera_plane(player);
	player->rot_speed = 0.05; // For the Field Of View, 0.66 comonly used for the type of game
	player->moving_forward = 0;
	player->moving_backward = 0;
	player->strafing_left = 0;
	player->strafing_right = 0;
	// printf("Player spawn: x=%f, y=%f (map_height=%d)\n", player->x, player->y, map_height);
}

void	init_map(t_map *map, t_parse *data)
{
	map->grid = data->map;
	map->width = ft_strlen(map->grid[0]);
	map->height = 0;
	while (map->grid[map->height])
		map->height++;
	init_door(map);
}

void	init_mini_map(t_mini_map *mini_map)
{
	mini_map->offset_x = 0;
	mini_map->offset_y = 0;
	mini_map->tile_size = MINIMAP_TILE_SIZE;
	mini_map->num_rays = 100;
	mini_map->ray_length = 0;
	mini_map->player_mini_x = 0;
	mini_map->player_mini_y = 0;
	mini_map->player_size = 0;
	mini_map->color = 0;
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

//A partir daqui ja esto funcoes a mais.
//Vou acrescentar aqui mais para depois passar para outro ficheiro

