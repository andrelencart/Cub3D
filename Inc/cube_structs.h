#ifndef CUBE_STRUCTS_H
# define CUBE_STRUCTS_H

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

// This is mine from fdf: Change what u need to change
typedef struct s_map
{
	// char 	**mtz;
	// int		ang[3];
	// int		scale;
	// int		z_scale;
	// float	zoom;
	// float	orig_cord[3];
	// int		hait;
	// int		with;
}			t_map;

typedef struct s_cube
{
	t_map		map;
	t_window	window;
}				t_cube;

#endif //CUBE_STRUCTS_H