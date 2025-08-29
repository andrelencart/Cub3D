#include "../../Inc/cube3d.h"

int	lookfor_mons_texture(char *tex)
{
	int		fd;

	fd = open(tex, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(STDERR_FILENO, "Error\nCube3d: \"%s\": ", tex);
		return (ft_putendl_fd(strerror(errno), 2), 1);
	}
	close(fd);
	return (test_mlx_texture(tex));
}