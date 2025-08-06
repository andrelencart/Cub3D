#include "../../Inc/cube3d.h"

int	padd_map_end(t_parse *data, int x)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] != 0)
			j++;
		while (j < x)
		{
			data->map[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (0);
}

int	allocate_square_map(t_parse *data, int i, int x)
{
	char	**tmp;
	int		j;

	tmp = ft_calloc(i + 1, sizeof(char *));
	if (!tmp)
		return (parse_error("square_map(): No allocation of **tmp"));
	i = 0;
	while (data->map[i])
	{
		j = 0;
		tmp[i] = ft_calloc(x + 1, sizeof(char));
		if (!tmp[i])
		{
			free_split(tmp);
			return (parse_error("square_map(): No allocation of *tmp"));
		}
		while (data->map[i][j] != 0 && data->map[i][j++] != '\n')
			tmp[i][j - 1] = data->map[i][j - 1];
		i++;
	}
	free_split(data->map);
	data->map = tmp;
	return (padd_map_end(data, x));
}

int	square_map(t_parse *data)
{
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	x = 0;
	while (data->map[i])
	{
		j = ft_strlen(data->map[i]);
		if (j > 0 && data->map[i][j - 1] == '\n')
			j = j - 1;
		if (j > x)
			x = j;
		i++;
	}
	return (allocate_square_map(data, i, x));
}
