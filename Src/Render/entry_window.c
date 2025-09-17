#include "../../Inc/cube3d.h"

void	game_menu(t_cube *cube)
{
	int	width;
	int	height;

	cube->menu_img.img = mlx_xpm_file_to_image(cube->window.mlx, \
"./textures/monster/monster_rr_3.xpm", &width, &height);
	if (!cube->menu_img.img)
		return ;
	cube->menu_img.addr = mlx_get_data_addr(cube->menu_img.img, &cube->menu_img.bitpp, \
&cube->menu_img.line_length, &cube->menu_img.endian);
	mlx_put_image_to_window(cube->window.mlx, cube->window.mlx_window, cube->menu_img.img, 100, 100);
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, 200, 200, 0xFFFFFF, "Press ENTER to start");
}
