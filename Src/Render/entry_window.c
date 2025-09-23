#include "../../Inc/cube3d.h"

void	game_menu(t_cube *cube)
{
	mlx_put_image_to_window(cube->window.mlx, cube->window.mlx_window, \
cube->menu_img.img, (WIND_WIDTH / 2) - 400, (WIND_HEIGHT / 2) - 300);
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
910, 910, 0xFFFFFF, "Press ENTER to start");
}
