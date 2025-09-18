#include "../../Inc/cube3d.h"

int	change_pixel(double fade, int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * fade);
	g = (int)(g * fade);
	b = (int)(b * fade);
	return ((r << 16) | (g << 8) | b);
}

void	fade_out(t_cube *cube)
{
	int		x;
	int		y;
	char	*pixel;

	if (cube->enemy.fade_timer % 3 == 0)
	{
		y = 0;
		while (y < WIND_HEIGHT)
		{
			x = 0;
			while (x < WIND_WIDTH)
			{
				pixel = cube->game_img.addr + (y * cube->game_img.line_length + x * \
(cube->game_img.bitpp / 8));
				*(int *)pixel = change_pixel(cube->enemy.fade, *(int *)pixel);
				x++;
			}
			y++;
		}
		cube->enemy.fade_timer = 0;
	}
	cube->enemy.fade_timer++;
}

void	put_pixel(t_cube *cube, t_sprite *sprite, int x, int y)
{
	int		screen_x;
	int		screen_y;
	int		color;
	char	*dst;

	color = *(int *)(sprite->addr + (((int)((double)y / sprite->factor)) * \
sprite->line + ((int)((double)x / sprite->factor)) * (sprite->bpp / 8)));
	if ((color & 0x00FFFFFF) != 0)
	{
		screen_x = sprite->draw_s_x + x;
		screen_y = sprite->draw_s_y + y;
		if (screen_x >= 0 && screen_x < WIND_WIDTH && screen_y >= 0 \
&& screen_y < WIND_HEIGHT)
		{
			dst = cube->game_img.addr + (screen_y * cube->game_img.line_length + \
screen_x * (cube->game_img.bitpp / 8));
			*(int *)dst = color;
		}
	}
}

void	draw_scaled_sprite(t_cube *cube, t_sprite *sprite)
{
	int		x;
	int		y;

	sprite->sprt_w = sprite->width * sprite->factor;
	sprite->sprt_h = sprite->height * sprite->factor;
	y = 0;
	while (y < sprite->sprt_h)
	{
		x = 0;
		while (x < sprite->sprt_w)
		{
			put_pixel(cube, sprite, x, y);
			x++;
		}
		y++;
	}
}

void	death_monster(t_cube *cube)
{
	t_sprite	*sprite;

	cube->enemy.anim_time += cube->frame_time;
	if (cube->enemy.anim_time >= cube->enemy.anim_speed)
	{
		cube->enemy.frame++;
		if (cube->enemy.frame >= 4)
			cube->enemy.frame = 0;
		cube->enemy.anim_time = 0;
	}
	sprite = &cube->enemy.front[cube->enemy.frame];
	sprite->factor = 35.0;
	sprite->draw_s_x = (WIND_WIDTH / 2) - (sprite->width * sprite->factor / 2);
	sprite->draw_s_y = 0;
	draw_scaled_sprite(cube, sprite);
	mlx_put_image_to_window(cube->window.mlx, cube->window.mlx_window, \
cube->game_img.img, 0, 0);
}
