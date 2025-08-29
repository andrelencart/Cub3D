#include "../../Inc/cube3d.h"

int	test_open(char *tex)
{
	int		fd;

	fd = open(tex, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(STDERR_FILENO, "Error\nCube3d: \"%s\": ", tex);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	close(fd);
	if (test_mlx_texture(tex))
		return (1);
	return (0);
}

int	look_mon_tex(char *tex, char t)
{
	int		i;

	if (!tex)
		return (parse_error("Failed to allocate monster texture path\
 for verification", NULL));
	i = 0;
	while (tex[i] != 'X')
		i++;
	tex[i] = 0 + '0';
	while (tex[i] != '4')
	{
		if (test_open(tex))
			return (free(tex), 1);
		tex[i] += 1;
		if (tex[i] == '4' && tex[i - 2] != t)
		{
			tex[i - 2] = t;
			tex[i] = 0 + '0';
		}
	}
	return (free(tex), 0);
}
