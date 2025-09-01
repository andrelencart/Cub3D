#include "../../Inc/cube3d.h"

void	draw_sprite(t_sprite *img, t_player *player, void *ptrmlx)
{
	img->sprite_x = img->x - player->x;
	img->sprite_y = img->y - player->y;

	img->inv_det = 1.0 / (player->plane_x * player->dir_y - \
player->plane_y * player->dir_x);
	img->trans_x = img->inv_det * (player->dir_y * img->sprite_x - \
player->dir_x * img->sprite_y);
	img->trans_y = img->inv_det * (-player->plane_y * img->sprite_x + \
player->plane_x * img->sprite_y);

	img->sprt_scrn_x = (int)((WIND_WIDTH / 2) * \
(1 + img->trans_x / img->trans_y));
	img->sprt_h = abs((int)(WIND_HEIGHT / img->trans_y));
	img->sprt_w = abs((int)(WIND_WIDTH / img->trans_y));

	img->draw_s_y = -img->sprt_h / 2 + WIND_HEIGHT / 2;
	if (img->draw_s_y < 0)
		img->draw_s_y = 0;
	img->draw_e_y = img->sprt_h / 2 + WIND_HEIGHT / 2;
	if (img->draw_e_y >= WIND_HEIGHT)
		img->draw_e_y = WIND_HEIGHT - 1;
	img->draw_s_x = -img->sprt_w / 2 + img->sprt_scrn_x;
	if (img->draw_s_x < 0)
		img->draw_s_x = 0;
	img->draw_e_x = img->sprt_w /2 + img->sprt_scrn_x;
	if (img->draw_e_x >= WIND_WIDTH)
		img->draw_e_x = WIND_WIDTH - 1;
}

void	draw_monster(t_enemy *enemy, t_player *player, void *ptrmlx)
{
	enemy->front->pos_x = enemy->monster.x;
	enemy->front->pos_y = enemy->monster.y;
	draw_sprite(enemy->front, player, ptrmlx);
}