

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
	init_map(&cube->map, data);
	init_player(&cube->player, data, cube->map.height);
	init_mini_map(&cube->mini_map);
	if (init_imgsmap(cube->window.mlx, &cube->imgsmap, data))
	{
		free_data(data);
		close_window(cube);
	}
}

void	init_player(t_player *player, t_parse *data, int map_height)
{
	player->x = data->player_x + 0.5; // x Position
	player->y = (map_height - 1 - data->player_y) + 0.5; // y Position (INVERTED)
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
	// printf("Player spawn: x=%f, y=%f (map_height=%d)\n", player->x, player->y, map_height);
}

void	init_map(t_map *map, t_parse *data)
{
	map->grid = data->map;
	map->width = strlen(map->grid[0]);
	map->height = 0;
	while (map->grid[map->height])
		map->height++;
	// for (int i = 0; map->grid[i]; i++) {
	// 	printf("map line %d: %s\n", i, map->grid[i]);
	// }
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

//A partir daqui ja esto funcoes a mais.
//Vou acrescentar aqui mais uma para depois passar para outro ficheiro
void	destroy_maps(void *ptrmlx, t_imgsmap *imgsmap)
{
	if (imgsmap->north.img)
		mlx_destroy_image(ptrmlx, imgsmap->north.img);
	if (imgsmap->south.img)
		mlx_destroy_image(ptrmlx, imgsmap->south.img);
	if (imgsmap->east.img)
		mlx_destroy_image(ptrmlx, imgsmap->east.img);
	if (imgsmap->west.img)
		mlx_destroy_image(ptrmlx, imgsmap->west.img);
}

int	close_window(t_cube *cube)
{
	destroy_maps(cube->window.mlx, &cube->imgsmap);
	free_split(cube->map.grid);
	mlx_destroy_image(cube->window.mlx, cube->window.img);
	mlx_destroy_window(cube->window.mlx, cube->window.mlx_window);
	mlx_destroy_display(cube->window.mlx);
	free(cube->window.mlx);
	exit(0);
}
