
#include "../../Inc/cube3d.h"

void	init_imgsmap(t_imgsmap *imgsmap, t_parse *data)
{
	imgsmap->ceiling = data->ceiling;
	imgsmap->floor = data->floor;
	imgsmap->north.img = NULL;
	imgsmap->north.addr = NULL;
	imgsmap->south.img = NULL;
	imgsmap->south.addr = NULL;
	imgsmap->east.img = NULL;
	imgsmap->east.addr = NULL;
	imgsmap->west.img = NULL;
	imgsmap->west.addr = NULL;
}
