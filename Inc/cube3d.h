/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:38:00 by andcarva          #+#    #+#             */
/*   Updated: 2025/09/25 18:58:45 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

// LIBS
# include "Libft/libft.h"
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
# include "cube_parse.h"

// MAP_DEF
# define WIND_WIDTH 1920
# define WIND_HEIGHT 1080
# define TILE_SIZE 20

// MATH
# define PI 3.141592653589793238462643383279502884197169399375105820974944592

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
# define E 101
# define ENTER 65293

// COLOR_DEF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000 
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define CEILING_COLOR_DK_G 0x333333
# define FLOOR_COLOR_LGHT_G 0xAAAAAA
# define WALL_COLOR_MG 0x666666
# define WALL_COLOR_MB 0x225588
# define DOOR_COLOR 0x8B0000
# define EXIT_COLOR 0x4D4D4D

// UTILS
# define DIM_FACTOR 1
# define LIGHT_RAD 1.7
# define MOVE_SPEED 1.5
# define SENSITIVITY 0.0017
# define DOOR_SPEED 0.2
# define PLAYER_COLL_RAD 0.2
# define PLAYER_INTERACTION 0.9
# define MINIMAP_VIEW_SIZE 11
# define MINIMAP_TILE_SIZE 20
# define MAX_MINIMAP_SIZE 32

// ERRORS
# define ERROR_ARGS "WRONG NUMBER OF ARGUMENTS"
# define ERROR_INIT "NOT INICIALIZED"
# define ERROR_MAP_LEN "MAP TO BIG"
# define ERROR_MAP "MAP EMPTY"
# define ERROR_SPACE "TO MANY SAPCES"
# define ERROR_CHAR "INVALID CHARACTER IN MAP"
# define ERROR_FORMAT "MAP NOT RETANGULAR"

// STRUCTS

typedef struct s_sprite
{
	void	*img;
	char	*addr;
	int		bpp;
	int		endian;
	int		line;
	int		width;//image width
	int		height;//image height
	double	pos_x;//position in map || posicion in texture x
	double	pos_y;//position in map || posicion in texture y
	double	sprite_x;//coord relative to player/camera
	double	sprite_y;
	double	inv_det;//for camera space coord
	double	trans_x;
	double	trans_y;
	int		sprt_scrn_x;//sprimove_speedte center in screen coord
	int		sprt_h;//sprite height || tex heigth * factor
	int		sprt_w;//sprite width || tex width * factor
	int		draw_s_y;//screen coord to start and end drawing // || draw start y
	int		draw_e_y;
	int		draw_s_x;// || draw start x
	int		draw_e_x;
	double	factor;// || zoom in end
}	t_sprite;

//Wall textures, floor & ceiling colors
typedef struct s_imgsmap
{
	t_sprite	north;
	t_sprite	south;
	t_sprite	east;
	t_sprite	west;
	t_sprite	door;
	t_sprite	exit;
	int			floor;
	int			ceiling;
}	t_imgsmap;

typedef struct s_window
{
	void	*mlx;
	void	*mlx_window;
}			t_window;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bitpp;
	int		line_length;
	int		endian;
}			t_image;

typedef struct s_player
{
	double	x;			// Player position, in the map
	double	y;
	double	dir_x;		// Direction vector
	double	dir_y;
	double	init_pos_x;
	double	init_pos_y;
	double	plane_x;	// Camera plane for FOV
	double	plane_y;
	double	rot_speed;
	double	move_speed;
	int		moving_forward;
	int		moving_backward;
	int		strafing_left;
	int		strafing_right;
	int		is_crouching;
}			t_player;

typedef enum e_state
{
	MENU,
	GAME,
	WANDER,
	PURSUIT,
	GAME_OVER,
	GAME_RESTART
}	t_state;

typedef struct s_enemy
{
	t_player	monster;
	t_sprite	front[4];
	t_sprite	frigt[4];
	t_sprite	back[4];
	t_sprite	blft[4];
	t_sprite	left[4];
	t_sprite	lfrt[4];
	t_sprite	right[4];
	t_sprite	rtbck[4];
	t_state		state;
	double		last_x;
	double		last_y;
	double		speed;
	int			frame;
	double		anim_time;
	double		anim_speed;
	double		fade;
	int			fade_timer;
}				t_enemy;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	camera_x;
	int		map_x;
	int		map_y;
	double	wall_x;
	double	perp_wall_dist;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit;
	int		hit_door;
	int		hit_exit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	raydir_light[4];
}			t_ray;

typedef struct s_door
{
	int		cord_x;
	int		cord_y;
	double	state;// 0.0 closed | 1.0 opened
	int		anim_state;// 1 opened | -1 closed | 0 idle
}			t_door;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	t_door	*doors;
	int		n_doors;
}			t_map;

typedef struct s_light
{
	double	radius;
	double	min;
	double	max;
	double	player_angle;
	double	start_angle;
	double	end_angle;
	double	m_m_fov;
}			t_light;

typedef struct s_mini_map
{
	int		offset_x;
	int		offset_y;
	int		player_size;
	int		player_mini_x;
	int		player_mini_y;
	int		num_rays;
	int		ray_length;
	int		tile_size;
	int		color;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	t_light	light;
}			t_mini_map;

typedef struct s_cube
{
	t_map			map;
	t_mini_map		mini_map;
	t_ray			ray;
	t_window		window;
	t_player		player;
	t_imgsmap		imgsmap;
	t_light			light;
	t_enemy			enemy;
	t_state			state;
	t_image			game_img;
	t_image			menu_img;
	t_parse			*data;
	double			frame_time;
	double			*zbuffer;
	int				mouse_warp;
	struct timeval	last_time;
}					t_cube;

// RENDER FUNCTIONS

// INIT

int				init(t_cube *cube, t_parse *data);
void			init_lighting(t_light *light);
void			init_player(t_player *player, t_parse *data, int map_height);
int				init_map(t_map *temap, t_parse *data);
int				init_door(t_map *map);
void			init_the_door(t_map *map, int y, int x, int *d);
void			init_mini_map(t_mini_map *mini_map);
int				init_window(t_cube *cube);
void			init_ray(t_player *player, t_ray *ray, int x);
void			init_ray(t_player *player, t_ray *ray, int x);
void			init_dda(t_player *player, t_ray *ray);
void			init_steps(t_player *player, t_ray *ray);
void			set_player_camera_plane(t_player *player);
int				init_imgsmap(void *ptrmlx, t_imgsmap *imgsmap, t_parse *data);
int				load_imgsmaps(void *ptrmlx, t_sprite *sprite, char *filepath);

// HOOKS

int				testkey(int key_code, t_window *wind);
void			hook_control(t_cube *cube);
int				loop_hook(t_cube *cube);
int				key_press(int key_code, t_cube *cube);
int				key_release(int key_code, t_cube *cube);
int				move_update_flag_release(int keycode, t_cube *cube);
int				move_update_flag_press(int keycode, t_cube *cube);

// DRAW

void			draw(t_cube *cube);
void			my_mlx_pixel_put(t_image *win, int x, int y, int color);
void			raycast(t_cube *cube);
int				raycast_wall_hit(t_ray *ray, int map_height, int map_width);
void			dda_loop(t_ray *ray, char **map, int map_height, int map_width);
void			calc_wall_dist(t_player *player, t_ray *ray);
void			draw_3d_map(t_cube *cube, t_ray *ray, int x);
int				get_texture_color(t_cube *cube, t_ray *ray, int y);
void			draw_monster(t_enemy *enemy, t_cube *cube);
void			calculate_sprite(t_sprite *img, t_player *player, t_cube *cube);
void			fade_out(t_cube *cube);

// LIGHT

unsigned int	dim_color(unsigned int color, double factor);
void			wall_light(t_cube *cube, t_ray *ray, double *factor);
void			get_row_distance_and_rays(t_cube *cube, int y, \
double *row_distance);
void			compute_floor_pos(int x, double row_distance, \
t_cube *cube, double floor[2]);
double			get_light_factor(double px, double py, \
t_player *player, t_light *light);

// MINI MAP

void			draw_tile(t_cube *cube, int start_x, int start_y, int color);
void			draw_mini_map(t_cube *cube);
void			draw_centered_mini_map(t_cube *cube, int half_view);
void			draw_player_mini_map(t_cube *cube, int half_view);
void			vision_mini_map(t_cube *cube, int half_view);
void			get_mini_map_color(t_cube *cube, int x, int y, int half_view);
void			vision_mini_map_init(t_cube *cube, int half_view);
void			mini_map_vision_draw(t_cube *cube, int draw_x, int draw_y);

// MONSTER

int				init_monster(t_cube *cube, t_parse *data, bool first);
void			monster_logic(t_cube *cube);
void			death_monster(t_cube *cube);

// DOORS

void			door_interaction(t_map *map, t_player *player);
void			update_door_animation(t_map *map);
void			count_doors(t_map *map);
t_door			*find_door(t_map *map, int x, int y);
void			state_of_animation(t_map *map, t_door *door);
void			exit_interaction(t_map *map, t_player *player);

// UTILS

int				get_tile_color(char c, t_cube *cube);
void			update_frame_time(t_cube *cube);
void			walls(t_cube *cube, t_ray *ray, int x, int *y);
void			floors(t_cube *cube, double floor[2], int x, int *y);
void			calc_wall_x(t_ray *ray, t_player *player);
int				can_move(t_cube *cube, double x, double y, double radius);
int				is_wall(t_cube *cube, double x, double y);
void			game_menu(t_cube *cube);
void			game_restart(t_cube *cube);
void			free_sprites(t_cube *cube);
// void			print_map(t_map *map);

// PLAYER MOVEMENT

int				player_rotation(t_player *player, int key_code);
int				rotate_player(t_player *player, double rot_speed);
int				player_move_left_right(t_player *player, \
t_cube *cube, double frame_time);
int				player_move_front_back(t_player *player, \
t_cube *cube, double frame_time);
int				mouse_move_handler(int x, int y, t_cube *cube);
int				window_edge_rotation(int *last_x, int x, \
t_cube *cube, double sensitivity);

// CLOSE

int				close_window(t_cube *cube);
void			destroy_maps(t_cube *cube);
void			exit_clean(t_cube *cube);

#endif //CUBE3D_H