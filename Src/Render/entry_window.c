#include "../../Inc/cube3d.h"

// void	game_menu(t_cube *cube)
// {
// 	int	x;
// 	int	y;

// 	x = 20;
// 	while (x < 40)
// 	{
// 		y = 20;
// 		while (y < 40)
// 		{
// 			my_mlx_pixel_put(&cube->window, x, y, RED);
// 			y++;
// 		}
// 		x++;
// 	}
// 	mlx_put_image_to_window(cube->window.mlx, \
// cube->window.mlx_window, cube->window.img, x, y);
// }

void game_menu(t_cube *cube)
{
	int	width;
	int	height;

	cube->window.img = mlx_xpm_file_to_image(cube->window.mlx, "/home/andcarva/Documents/Github/Cmn_Core/Milestone-4/42_Cube3D/textures/monster/monster_rr_3.xpm", &width, &height);
	mlx_put_image_to_window(cube->window.mlx, cube->window.mlx_window, cube->window.img, 100, 100);
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, 200, 200, 0xFFFFFF, "Press ENTER to start");
}
