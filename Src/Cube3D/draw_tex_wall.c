
#include "../../Inc/cube3d.h"

//Isto provavelmente tera que ir para outro ficheiro
t_sprite	get_tex_side(t_ray *ray, t_imgsmap *imgsmap)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (imgsmap->west);
		else
			return (imgsmap->east);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (imgsmap->north);
		else
			return (imgsmap->south);
	}
}

int	get_y_coord(t_ray *ray, int y, int sprite_y)
{
	int d;
	
	d = y * 256 - WIND_HEIGHT * 128 + ray->line_height * 128;
	return (((d * sprite_y) / ray->line_height) / 256);
}

int	get_texture_color(t_imgsmap *imgsmap, t_ray *ray, int y)
{
	t_sprite	sprite;
	int			tex_x;
	int			tex_y;
	char		*pixel;

	sprite = get_tex_side(ray, imgsmap);
	tex_x = (int)(ray->wall_x * sprite.x);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = sprite.x - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = sprite.x - tex_x - 1;
	tex_y = get_y_coord(ray, y, sprite.y);
	pixel = sprite.addr + (tex_y * sprite.line + tex_x * (sprite.bpp / 8));
	return (*(unsigned int*)pixel);
}
//o que esta daqui para cima deve ir para outro ficheiro

