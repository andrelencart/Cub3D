/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:41:08 by andcarva          #+#    #+#             */
/*   Updated: 2025/09/24 15:41:11 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/cube3d.h"

t_sprite	*get_tex_side(t_ray *ray, t_imgsmap *imgsmap)
{
	if (ray->hit_door == 1)
		return (&imgsmap->door);
	if (ray->hit_exit == 1)
		return (&imgsmap->exit);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&imgsmap->west);
		else
			return (&imgsmap->east);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&imgsmap->north);
		else
			return (&imgsmap->south);
	}
}

int	get_y_coord(t_ray *ray, int y, int sprite_y)
{
	int	d;

	d = y * 256 - WIND_HEIGHT * 128 + ray->line_height * 128;
	return (((d * sprite_y) / ray->line_height) / 256);
}

int	get_texture_color(t_cube *cube, t_ray *ray, int y)
{
	t_sprite	*sprite;
	int			tex_x;
	int			tex_y;
	char		*pixel;

	sprite = get_tex_side(ray, &cube->imgsmap);
	tex_x = (int)(ray->wall_x * sprite->width);
	if (cube->player.init_pos_y != 0)
	{
		if (ray->side == 0 && ray->ray_dir_x < 0)
			tex_x = sprite->width - tex_x - 1;
		if (ray->side == 1 && ray->ray_dir_y > 0)
			tex_x = sprite->width - tex_x - 1;
	}
	else
	{
		if (ray->side == 0 && ray->ray_dir_x < 0)
			tex_x = sprite->width - tex_x - 1;
		if (ray->side == 1 && ray->ray_dir_y > 0)
			tex_x = sprite->width - tex_x - 1;
	}
	tex_y = get_y_coord(ray, y, sprite->height);
	pixel = sprite->addr + (tex_y * sprite->line + tex_x * (sprite->bpp / 8));
	return (*(unsigned int *)pixel);
}
