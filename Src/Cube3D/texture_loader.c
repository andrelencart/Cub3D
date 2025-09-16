#include "../../Inc/cube3d.h"

int	load_doormaps(void *ptrmlx, t_sprite *sprite, char *filepath)
{
	sprite->img = NULL;
	sprite->addr = NULL;
	sprite->img = mlx_xpm_file_to_image(ptrmlx, filepath, &sprite->width, \
&sprite->height);
	if (!sprite->img)
		return (1);
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bpp, \
&sprite->line, &sprite->endian);
	if (!sprite->addr)
	{
		mlx_destroy_image(ptrmlx, sprite->img);
		return (1);
	}
	return (0);
}

int	load_imgsmaps(void *ptrmlx, t_sprite *sprite, char *filepath)
{
	sprite->img = NULL;
	sprite->addr = NULL;
	sprite->img = mlx_xpm_file_to_image(ptrmlx, filepath, &sprite->width, \
&sprite->height);
	if (!sprite->img)
		return (1);
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bpp, \
&sprite->line, &sprite->endian);
	if (!sprite->addr)
	{
		mlx_destroy_image(ptrmlx, sprite->img);
		return (1);
	}
	return (0);
}

int	init_imgsmap(void *ptrmlx, t_imgsmap *imgsmap, t_parse *data)
{
	imgsmap->ceiling = data->ceiling;
	imgsmap->floor = data->floor;
	if (load_imgsmaps(ptrmlx, &imgsmap->north, data->n_face))
		return (parse_error("Failed to load texture", data->n_face));
	if (load_imgsmaps(ptrmlx, &imgsmap->south, data->s_face))
		return (parse_error("Failed to load texture", data->s_face));
	if (load_imgsmaps(ptrmlx, &imgsmap->east, data->e_face))
		return (parse_error("Failed to load texture", data->e_face));
	if (load_imgsmaps(ptrmlx, &imgsmap->west, data->w_face))
		return (parse_error("Failed to load texture", data->w_face));
	if (load_doormaps(ptrmlx, &imgsmap->door, "./textures/walls/exit.xpm"))
		return (parse_error("Failed to load texture", data->w_face));
	return (0);
}
