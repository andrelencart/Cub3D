

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
# define WIND_WIDTH 1920
# define WIND_HEIGHT 1080
# define TILE_SIZE 20

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
# define CEILING_COLOR_DK_G 0x333333
# define FLOOR_COLOR_LGHT_G 0xAAAAAA
# define WALL_COLOR_MG 0x666666
# define WALL_COLOR_MB 0x225588

// // CORD_DEF
// # define X 0
// # define Y 1
// # define Z 2

// ERRORS
# define ERROR_ARGS "WRONG NUMBER OF ARGUMENTS"
# define ERROR_INIT "NOT INICIALIZED"
# define ERROR_MAP_LEN "MAP TO BIG"
# define ERROR_MAP "MAP EMPTY"
# define ERROR_SPACE "TO MANY SAPCES"
# define ERROR_CHAR "INVALID CHARACTER IN MAP"
# define ERROR_FORMAT "MAP NOT RETANGULAR"

// MAP's

// char *test_map[] = {
// 	"1111111111",
//     "1000000001",
//     "1011111101",
//     "1010000101",
//     "1010P00101",
//     "1010111101",
//     "1000000001",
//     "1111111111",
//     NULL
// };

// static char *test_map[] = {
//     "111111",
//     "100001",
//     "100001",
//     "111111",
// 	NULL
// };

// STRUCTS

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

typedef struct s_player
{
	double	x;			// Player position, in the map
	double	y;
	double	dir_x;		// Direction vector
	double	dir_y;
	double	plane_x;	// Camera plane for FOV
	double	plane_y;
	double	rot_speed;
	int		moving_forward;
	int		moving_backward;
	int		strafing_left;
	int		strafing_right;
}			t_player;

typedef struct  s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	camera_x;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}			t_ray;

typedef	struct s_map
{
	char	**grid;
	int		width;
	int		height;
}			t_map;

typedef	struct s_mini_map
{
	int		offset_x;
	int		offset_y;
	int 	player_size;
	int		player_mini_x;
	int		player_mini_y;
	int 	num_rays;
	int 	ray_length;
	int		tile_size;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
}			t_mini_map;

typedef struct s_cube
{
	t_map			map;
	t_mini_map		mini_map;
	t_ray			ray;
	t_window		window;
	t_player		player;
	double			frame_time;
	struct timeval	last_time;
}					t_cube;

// RENDER FUNCTIONS

// INIT

void	init(t_cube *cube);
void	init_player(t_player *player);
void	init_map(t_map *temap);
void	init_mini_map(t_mini_map *mini_map);
void	init_window(t_window *window);
void	init_ray(t_player *player, t_ray *ray, int x);
void	init_ray(t_player *player, t_ray *ray, int x);
void	init_dda(t_player *player, t_ray *ray);
void	init_steps(t_player *player, t_ray *ray);

// HOOKS

int		testkey(int key_code, t_window *wind);
void	hook_control(t_cube *cube);
int		loop_hook(t_cube *cube);
int		key_press(int key_code, t_cube *cube);
int		key_release(int key_code, t_cube *cube);
int		move_update_flag_release(int keycode, t_cube *cube);
int		move_update_flag_press(int keycode, t_cube *cube);

// DRAW

void	draw(t_cube *cube);
void	my_mlx_pixel_put(t_window *win, int x, int y, int color);
void	raycast(t_cube *cube);
void	dda_loop(t_ray *ray, char **map);
void	calc_wall_dist(t_player *player, t_ray *ray);
void	draw_3d_map(t_window *win, t_ray *ray, int x);

// MINI MAP
void	draw_tile(t_window *win, int start_x, int start_y, int color);
void	draw_mini_map(t_cube *cube);
void	draw_player_mini_map(t_cube *cube);
void	draw_vision_mini_map(t_cube *cube);

// UTILS

int		get_tile_color(char c);
void	update_frame_time(t_cube *cube);

// PLAYER MOVEMENT

int		player_rotation(t_player *player, int key_code);
int		rotate_player(t_player *player, double rot_speed);
int		player_move_left_right(t_player *player, char **map, double frame_time);
int		player_move_front_back(t_player *player, char **map, double frame_time);

// CLOSE

int		close_window(t_window *window);

#endif //CUBE3D_H