#include "../../Inc/cube3d.h"

void	draw_sprite_y(int col, int tex_x, t_sprite *img, t_cube *cube)
{
	unsigned int	color;
	int				y;
	int				d;
	int				tex_y;

	y = img->draw_s_y;
	if (y < 0)
		y = 0;
	while (y < img->draw_e_y && y < WIND_HEIGHT)
	{
		d = (y - img->draw_s_y) * 256; 
		tex_y = ((d * img->height) / img->sprt_h) / 256;
		color = *(unsigned int *)(img->addr + (tex_y * img->line + tex_x * \
(img->bpp / 8)));
		if ((color & 0xFF000000) != 0xFF000000)
			my_mlx_pixel_put(&cube->window, col, y, dim_color(color, img->factor));
		y++;
	}
}

void	draw_sprite_x(t_sprite *img, t_cube * cube)
{
	int		col;
	int		tex_x;
	double	dist;

	dist = sqrt(img->sprite_x * img->sprite_x + img->sprite_y * img->sprite_y);
	if (dist <= cube->light.radius)
		img->factor = cube->light.min + (cube->light.max - cube->light.min) * \
(1.0 - dist / cube->light.radius);
	else
		img->factor = cube->light.min;
	col = img->draw_s_x;
	while (col <= img->draw_e_x)
	{
		tex_x = (int)(256 * (col - (-img->sprt_w / 2 + img->sprt_scrn_x)) * \
img->width / img->sprt_w) / 256;
		if (img->trans_y > 0 && col > 0 && col < WIND_WIDTH && img->trans_y < \
cube->zbuffer[col])
			draw_sprite_y(col, tex_x, img, cube);
		col++;
	}
}

void	calculate_sprite(t_sprite *img, t_player *player, t_cube * cube)
{
	img->sprite_x = img->pos_x - player->x;
	img->sprite_y = img->pos_y - player->y;
	img->inv_det = 1.0 / (player->plane_x * player->dir_y - \
player->plane_y * player->dir_x);
	img->trans_x = img->inv_det * (player->dir_y * img->sprite_x - \
player->dir_x * img->sprite_y);
	img->trans_y = img->inv_det * (-player->plane_y * img->sprite_x + \
player->plane_x * img->sprite_y);
	img->sprt_scrn_x = (int)((WIND_WIDTH / 2) * \
(1 + img->trans_x / img->trans_y));
	img->sprt_h = abs((int)(WIND_HEIGHT / img->trans_y));
	img->sprt_w = abs((int)(WIND_HEIGHT / img->trans_y));
	img->draw_s_y = -img->sprt_h / 2 + WIND_HEIGHT / 2;
	img->draw_e_y = img->sprt_h / 2 + WIND_HEIGHT / 2;
	img->draw_s_x = -img->sprt_w / 2 + img->sprt_scrn_x;
	if (img->draw_s_x < 0)
		img->draw_s_x = 0;
	img->draw_e_x = img->sprt_w /2 + img->sprt_scrn_x;
	if (img->draw_e_x >= WIND_WIDTH)
		img->draw_e_x = WIND_WIDTH - 1;
	draw_sprite_x(img, cube);
}

t_sprite	*find_monster_dir(t_enemy *enemy, int index)
{
	if (index >= 8)
		index = 0;
	if (index == 0)
		return (enemy->front);
	if (index == 1)
		return (enemy->frigt);
	if (index == 2)
		return (enemy->right);
	if (index == 3)
		return (enemy->rtbck);
	if (index == 4)
		return (enemy->back);
	if (index == 5)
		return (enemy->blft);
	if (index == 6)
		return (enemy->left);
	if (index == 7)
		return (enemy->lfrt);
	return (enemy->front);
}

void	draw_monster(t_enemy *enemy, t_player *player, t_cube *cube)
{
	double	dx;
	double	dy;
	double	relative_angle;
	t_sprite	*dir;

	dx = cube->player.x - enemy->monster.x;
	dy = cube->player.y - enemy->monster.y;
	relative_angle = (atan2(dy, dx) - atan2(enemy->monster.dir_y, \
enemy->monster.dir_x) + ((2 * PI / 8) / 2));
	while (relative_angle < 0)
		relative_angle += 2 * PI;
	while (relative_angle >= 2 * PI)
		relative_angle -= 2 * PI;
	dir = find_monster_dir(enemy, (int)(relative_angle / (PI / 4)));
	dir[enemy->frame].pos_x = enemy->monster.x;
	dir[enemy->frame].pos_y = enemy->monster.y;
	calculate_sprite(&dir[enemy->frame], player, cube);
}
