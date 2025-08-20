#include "../../Inc/cube3d.h"

int	test_mlx_texture(char *filepath)
{
	t_sprite	img;
	void		*ptrmlx;

	ptrmlx = NULL;
	img.img = NULL;
	img.addr = NULL;
	ptrmlx = mlx_init();
	if (!ptrmlx)
		return (parse_error("Mlx failed to initialize", NULL));
	img.img = mlx_xpm_file_to_image(ptrmlx, filepath, &img.x, &img.y);
	if (!img.img)
		return (mlx_destroy_display(ptrmlx), free(ptrmlx),\
parse_error("Mlx failed to open", filepath));
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line, &img.endian);
	if (!img.addr)
		return (mlx_destroy_display(ptrmlx), free(ptrmlx),\
parse_error("Mlx failed to get", filepath));
	mlx_destroy_image(ptrmlx, img.img);
	mlx_destroy_display(ptrmlx);
	free(ptrmlx);
	return (0);
}
