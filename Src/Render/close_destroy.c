#include "../../Inc/cube3d.h"

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
	free(cube->map.doors);
	mlx_destroy_image(cube->window.mlx, cube->game_img.img);
	mlx_destroy_image(cube->window.mlx, cube->menu_img.img);
	mlx_destroy_window(cube->window.mlx, cube->window.mlx_window);
	mlx_destroy_display(cube->window.mlx);
	free(cube->window.mlx);
	exit(0);
}
