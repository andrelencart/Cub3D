#ifndef CUBE_PARSE_H
# define CUBE_PARSE_H

# include <errno.h>

typedef struct s_parse
{
	char	*n_face;
	char	*s_face;
	char	*e_face;
	char	*w_face;
	int		floor;
	int		ceiling;
	char	**map;
}	t_parse;

//parse_cleaning.c
int		parse_error(char *msg);
void	free_data(t_parse *data);

//cube_checker.c
int		parse_check_fname(char *fname, t_parse *data);

//texture_checker.c
int		parse_textures(t_parse *data);

//checker_helper.c
int		check_line_end(char *str);
int		is_data_filled(t_parse *data);
int		lookfor_texture(char **dest);

//map_checker.c
int		check_map(t_parse *data, int i);

#endif
