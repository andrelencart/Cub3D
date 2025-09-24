/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:43:14 by andcarva          #+#    #+#             */
/*   Updated: 2025/09/24 15:43:15 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/cube3d.h"

void	hook_control(t_cube *cube)
{
	mlx_hook(cube->window.mlx_window, 17, 0, close_window, cube);
	mlx_key_hook(cube->window.mlx_window, testkey, cube);
	mlx_hook(cube->window.mlx_window, 2, 1L << 0, key_press, cube);
	mlx_hook(cube->window.mlx_window, 3, 1L << 1, key_release, cube);
	mlx_hook(cube->window.mlx_window, 6, 1L << 6, mouse_move_handler, cube);
}

int	key_press(int key_code, t_cube *cube)
{
	if (key_code == ESC)
		close_window(cube);
	else if (key_code == ENTER && cube->state == MENU)
		cube->state = GAME;
	else if (key_code == ENTER && cube->state == GAME_RESTART)
		cube->state = GAME;
	else if (key_code == RA || key_code == LA)
		player_rotation(&cube->player, key_code);
	else if (key_code == W || key_code == A || \
key_code == S || key_code == D)
		move_update_flag_press(key_code, cube);
	else if (key_code == E)
	{
		door_interaction(&cube->map, &cube->player);
		exit_interaction(&cube->map, &cube->player);
	}
	else if (key_code == SHIFT_LEFT || key_code == SHIFT_RIGHT)
		cube->player.move_speed = MOVE_SPEED + 0.5;
	return (0);
}

int	key_release(int key_code, t_cube *cube)
{
	if (key_code == W || key_code == A || \
key_code == S || key_code == D)
		move_update_flag_release(key_code, cube);
	else if (key_code == SHIFT_LEFT || key_code == SHIFT_RIGHT)
		cube->player.move_speed = MOVE_SPEED;
	return (0);
}

void	update_frame_time(t_cube *cube)
{
	struct timeval	current_time;
	double			seconds;

	gettimeofday(&current_time, NULL);
	seconds = (current_time.tv_sec - cube->last_time.tv_sec) \
+ (current_time.tv_usec - cube->last_time.tv_usec) / 1000000.0;
	cube->frame_time = seconds;
	cube->last_time = current_time;
}

int	loop_hook(t_cube *cube)
{
	update_frame_time(cube);
	if (cube->state == MENU)
		game_menu(cube);
	else if (cube->state == GAME)
	{
		if (cube->enemy.state != GAME_OVER)
		{
			player_move_front_back(&cube->player, cube, cube->frame_time);
			player_move_left_right(&cube->player, cube, cube->frame_time);
			monster_logic(cube);
			update_door_animation(&cube->map);
			draw(cube);
		}
		else
		{
			fade_out(cube);
			death_monster(cube);
		}
	}
	else if (cube->state == GAME_RESTART)
		game_restart(cube);
	return (0);
}
