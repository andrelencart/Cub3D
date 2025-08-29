#include "../../Inc/cube3d.h"

int	look_mon_tex(char *tex, char t)
{
	int		i;
	int		fd;

	i = 0;
	while (tex[i] != 'X')
		i++;
	tex[i] = 0 + '0';
	while (tex[i] != '4')
	{
		fd = open(tex, O_RDONLY);
		if (fd < 0)
			return (ft_printf_fd(STDERR_FILENO, "Error\nCube3d: \"%s\": ", tex), \
free(tex), ft_putendl_fd(strerror(errno), 2), 1);
		close(fd);
		if (test_mlx_texture(tex))
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
