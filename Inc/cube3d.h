/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:53:09 by andcarva          #+#    #+#             */
/*   Updated: 2025/07/17 16:05:40 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

// LIBS
# include "Libft/libft.h"
# include "cube_structs.h"
# include <limits.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include <unistd.h>
# include "../minilibx/mlx.h"
# include "../Inc/Libft/libft.h"

// Tudo o que eu coloquei aqui podes alterar,
// Isto sao coisas que eu tinha do FDF

// MAP_DEF
# define WIDTH 1920
# define HEIGHT 1080

// PROJECTION_KEYS
# define ISOMETRIC 0
# define FRONT_VIEW 1
# define SIDE_VIEW 2
# define TOP_VIEW 3

// MATH
# define PI 3.14159265358979323846

// KEY_DEF
# define ESC 65307
# define KBAR 65363
# define KBAL 65361
# define KBAU 65362
# define KBAD 65364
# define KB1 49
# define KB2 50
# define KB3 51
# define KB4 52
# define LA 65361
# define UP 65362
# define RA 65363
# define DOWN 65364
# define W 119
# define A 97
# define S 115
# define D 100
# define SRC_UP 4
# define SRC_DOWN 5
# define SHIFT_LEFT 65505
# define SHIFT_RIGHT 65506
# define P 112
# define M 109
# define R 114

// COLOR_DEF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000

// CORD_DEF
# define X 0
# define Y 1
# define Z 2

// ERRORS
# define ERROR_ARGS "TO MANY ARGUMENTS"
# define ERROR_INIT "NOT INICIALIZED"
# define ERROR_MAP_LEN "MAP TO BIG"
# define ERROR_MAP "MAP EMPTY"
# define ERROR_SPACE "TO MANY SAPCES"
# define ERROR_CHAR "INVALID CHARACTER IN MAP"
# define ERROR_FORMAT "MAP NOT RETANGULAR"

#endif //CUBE3D_H