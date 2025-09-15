

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
	init_door(&map->door);
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

void	destroy_image_array(t_sprite *array, void *ptrmlx)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(ptrmlx, array[i].img);
		i++;
	}
}

void	destroy_enemy_imgs(t_cube *cube)
{
	if (cube->enemy.back->img)
		destroy_image_array(cube->enemy.back, cube->window.mlx);
	if (cube->enemy.blft->img)
		destroy_image_array(cube->enemy.blft, cube->window.mlx);
	if (cube->enemy.frigt->img)
		destroy_image_array(cube->enemy.frigt, cube->window.mlx);
	if (cube->enemy.front->img)
		destroy_image_array(cube->enemy.front, cube->window.mlx);
	if (cube->enemy.left->img)
		destroy_image_array(cube->enemy.left, cube->window.mlx);
	if (cube->enemy.lfrt->img)
		destroy_image_array(cube->enemy.lfrt, cube->window.mlx);
	if (cube->enemy.right->img)
		destroy_image_array(cube->enemy.right, cube->window.mlx);
	if (cube->enemy.rtbck->img)
		destroy_image_array(cube->enemy.rtbck, cube->window.mlx);
}

void	destroy_maps(t_cube *cube)
{
	if (cube->imgsmap.north.img)
		mlx_destroy_image(cube->window.mlx, cube->imgsmap.north.img);
	if (cube->imgsmap.south.img)
		mlx_destroy_image(cube->window.mlx, cube->imgsmap.south.img);
	if (cube->imgsmap.east.img)
		mlx_destroy_image(cube->window.mlx, cube->imgsmap.east.img);
	if (cube->imgsmap.west.img)
		mlx_destroy_image(cube->window.mlx, cube->imgsmap.west.img);
	if (cube->imgsmap.door.img)
		mlx_destroy_image(cube->window.mlx, cube->imgsmap.door.img);
	destroy_enemy_imgs(cube);
}

int	close_window(t_cube *cube)
{
	if (cube->zbuffer)
		free(cube->zbuffer);
	destroy_maps(cube);
	free_split(cube->map.grid);
	mlx_destroy_image(cube->window.mlx, cube->window.img);
	mlx_destroy_window(cube->window.mlx, cube->window.mlx_window);
	mlx_destroy_display(cube->window.mlx);
	free(cube->window.mlx);
	exit(0);
}
