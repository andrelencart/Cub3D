/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:42:56 by andcarva          #+#    #+#             */
/*   Updated: 2025/09/24 15:42:58 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/cube3d.h"

void	game_menu(t_cube *cube)
{
	mlx_put_image_to_window(cube->window.mlx, cube->window.mlx_window, \
cube->menu_img.img, (WIND_WIDTH / 2) - 400, (WIND_HEIGHT / 2) - 300);
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
910, 910, 0xFFFFFF, "Press ENTER to start");
}

void	game_restart(t_cube *cube)
{
	mlx_put_image_to_window(cube->window.mlx, cube->window.mlx_window, \
cube->menu_img.img, (WIND_WIDTH / 2) - 400, (WIND_HEIGHT / 2) - 300);
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
326, 128, 0xFFFFFF, "ESCAPE IS AN ILLUSION!!");
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
700, 250, 0xFFFFFF, "THERE IS NO ESCAPE!!");
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
650, 450, 0xFFFFFF, "ETERNAL PAIN IF YOU PRESS ENTER!!");
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
275, 560, 0xFFFFFF, "ESCAPE IS FUTILE");
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
430, 780, 0xFFFFFF, "PRESS ENTER FOR MORE ANGUISH!!");
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
410, 920, 0xFFFFFF, "THERE IS NO HOPE!!");
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
940, 950, 0xFFFFFF, "YOU WILL FEED MY SOUL");
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
1250, 750, 0xFFFFFF, "PRESS ENTER FOR MORE NIGHTMARES");
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
1550, 470, 0xFFFFFF, "Press ENTER to DESPAIR!!");
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
1310, 230, 0xFFFFFF, "ABANDON ALL HOPE!!");
	mlx_string_put(cube->window.mlx, cube->window.mlx_window, \
1110, 800, 0xFFFFFF, "PRESS ENTER TO SUFFER!!");
}
