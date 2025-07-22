

#ifndef CUBE3D_H
# define CUBE3D_H

// LIBS
# include "Libft/libft.h"
// # include "cube_structs.h"
# include <limits.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>
# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include "../Inc/Libft/libft.h"

// Tudo o que eu coloquei aqui podes alterar,
// Isto sao coisas que eu tinha do FDF

// MAP_DEF
# define WIDTH 1920
# define HEIGHT 1080

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
# define ERROR_ARGS "WRONG NUMBER OF ARGUMENTS"
# define ERROR_INIT "NOT INICIALIZED"
# define ERROR_MAP_LEN "MAP TO BIG"
# define ERROR_MAP "MAP EMPTY"
# define ERROR_SPACE "TO MANY SAPCES"
# define ERROR_CHAR "INVALID CHARACTER IN MAP"
# define ERROR_FORMAT "MAP NOT RETANGULAR"

// STRUCTS

//This is the struct for the mlx window
typedef	struct s_window
{
	void	*mlx;
	void	*mlx_window;
	void	*img;
	char	*addr;
	int		bitpp;
	int		line_length;
	int		endian;
}			t_window;

// // This is mine from fdf: Change what u need to change
// typedef struct s_map
// {
// 	char 	**mtz;
// 	int		ang[3];
// 	int		scale;
// 	int		z_scale;
// 	float	zoom;
// 	float	orig_cord[3];
// 	int		hait;
// 	int		with;
// }			t_map;

typedef struct s_cube
{
	// t_map		map;
	t_window	window;
}				t_cube;

// RENDER FUNCTIONS

// INIT

void	init_window(t_window *window);

// HOOKS

void	hook_control(t_cube *cube);
int		key_press(int key_code, t_cube *cube);

// CLOSE

int		close_window(t_window *window);

#endif //CUBE3D_H