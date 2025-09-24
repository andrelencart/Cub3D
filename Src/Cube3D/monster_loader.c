#include "../../Inc/cube3d.h"

int	get_mon_tex(char *tex, void *ptrmlx, t_sprite *img)
{
	int		pos;
	int		count;

	if (!tex)
		return (parse_error("Failed to allocate monster texture path\
 for storing", NULL));
	pos = 0;
	while (tex[pos] != 'X')
		pos++;
	count = 0;
	while (count < 4)
	{
		tex[pos] = count + '0';
		if (load_imgsmaps(ptrmlx, &img[count], tex))
			return (parse_error("Failed to load texture", tex), free(tex), 1);
		count ++;
	}
	return (free(tex), 0);
}

int	load_mons_tex(t_cube *cube)
{
	if (get_mon_tex(ft_strdup("textures/monster/monster_bb_X.xpm"), \
cube->window.mlx, cube->enemy.back))
		return (1);
	if (get_mon_tex(ft_strdup("textures/monster/monster_bl_X.xpm"), \
cube->window.mlx, cube->enemy.blft))
		return (1);
	if (get_mon_tex(ft_strdup("textures/monster/monster_ff_X.xpm"), \
cube->window.mlx, cube->enemy.front))
		return (1);
	if (get_mon_tex(ft_strdup("textures/monster/monster_fr_X.xpm"), \
cube->window.mlx, cube->enemy.frigt))
		return (1);
	if (get_mon_tex(ft_strdup("textures/monster/monster_ll_X.xpm"), \
cube->window.mlx, cube->enemy.left))
		return (1);
	if (get_mon_tex(ft_strdup("textures/monster/monster_lf_X.xpm"), \
cube->window.mlx, cube->enemy.lfrt))
		return (1);
	if (get_mon_tex(ft_strdup("textures/monster/monster_rr_X.xpm"), \
cube->window.mlx, cube->enemy.right))
		return (1);
	if (get_mon_tex(ft_strdup("textures/monster/monster_rb_X.xpm"), \
cube->window.mlx, cube->enemy.rtbck))
		return (1);
	return (0);
}

int	init_monster(t_cube *cube, t_parse *data, bool first)
{
	if(first)
		ft_memset(&cube->enemy, 0, sizeof(t_enemy));
	cube->enemy.fade = 0.9;
	cube->enemy.fade_timer = 0;
	cube->enemy.monster.x = data->enemy_x + 0.5;
	cube->enemy.monster.y = data->enemy_y + 0.5;
	cube->enemy.monster.dir_x = cube->player.dir_x;
	cube->enemy.monster.dir_y = cube->player.dir_y;
	cube->enemy.monster.init_pos_x = cube->enemy.monster.x;
	cube->enemy.monster.init_pos_y = cube->enemy.monster.y;
	cube->enemy.monster.moving_backward = 0;
	cube->enemy.monster.moving_forward = 0;
	cube->enemy.monster.rot_speed = 0.05;
	cube->enemy.monster.strafing_left = 0;
	cube->enemy.monster.strafing_right = 0;
	cube->enemy.anim_speed = 0.08;
	if (first)
		return (load_mons_tex(cube));
	return (0);
}
