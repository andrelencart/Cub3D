#include "../../Inc/cube3d.h"

int	init(t_cube *cube, t_parse *data)
{
	ft_memset(cube, 0, sizeof(t_cube));
	if (init_window(cube))
		return (free_split(data->map), 1);
	if (init_map(&cube->map, data) == 1)
		return (1);
	init_player(&cube->player, data, cube->map.height);
	cube->zbuffer = ft_calloc(WIND_WIDTH, sizeof(double));
	if (!cube->zbuffer)
		return (ft_printf_fd(2, "Failed to allocate zbuffer memory"), 1);
	if (init_imgsmap(cube->window.mlx, &cube->imgsmap, data))
		return (1);
	if (init_monster(cube, data, true))
		return (1);
	init_mini_map(&cube->mini_map);
	init_lighting(&cube->light);
	cube->data = data;
	return (0);
}

void	init_player(t_player *player, t_parse *data, int map_height)
{
	(void)map_height;
	player->x = data->player_x + 0.5;
	player->y = data->player_y + 0.5;
	player->dir_x = data->player_dir_x;
	player->dir_y = data->player_dir_y;
	player->init_pos_x = data->player_dir_x;
	player->init_pos_y = data->player_dir_y;
	set_player_camera_plane(player);
	player->rot_speed = 0.05;
	player->moving_forward = 0;
	player->moving_backward = 0;
	player->strafing_left = 0;
	player->strafing_right = 0;
	player->move_speed = MOVE_SPEED;
}

int	init_map(t_map *map, t_parse *data)
{
	map->grid = data->map;
	map->width = ft_strlen(map->grid[0]);
	map->height = 0;
	while (map->grid[map->height])
		map->height++;
	if (init_door(map) == 1)
		return (1);
	return (0);
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

int	init_window(t_cube *cube)
{
	int	width;
	int	height;
	
	cube->window.mlx = mlx_init();
	cube->window.mlx_window = mlx_new_window(cube->window.mlx, WIND_WIDTH, \
WIND_HEIGHT, "CUBE3D");
	cube->game_img.img = mlx_new_image(cube->window.mlx, WIND_WIDTH, WIND_HEIGHT);
	cube->game_img.addr = mlx_get_data_addr(cube->game_img.img, &cube->game_img.bitpp, \
&cube->game_img.line_length, &cube->game_img.endian);
	cube->state = MENU;
	cube->menu_img.img = mlx_xpm_file_to_image(cube->window.mlx, \
"./textures/screen/monster_screen.xpm", &width, &height);
	if (!cube->menu_img.img)
		return (1);
	cube->menu_img.addr = mlx_get_data_addr(cube->menu_img.img, &cube->menu_img.bitpp, \
&cube->menu_img.line_length, &cube->menu_img.endian);
	return (0);
}
