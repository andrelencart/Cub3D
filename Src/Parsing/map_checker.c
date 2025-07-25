#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

int	check_map_line(char *line)
{
	if (!line)
		return (1);
	return (0);
}

int	check_map(t_parse *data, int i)
{
	int		j;
	int		k;
	char	**tmp;

	j = i;
	while (data->map[j])
		j++;
	tmp = ft_calloc(j - i + 1, sizeof(char *));
	if (!tmp)
		return (parse_error("Failed to allocate memory for map"));
	k = 0;
	while (i < j)
	{
		tmp[k] = ft_strdup(data->map[i]);
		if (!tmp[k])
			return (free_split(tmp), parse_error("Failed \
to allocate memory for map line"));
		if (check_map_line(tmp[k]))
			return (free_split(tmp), 1);
		i++;
		k++;
	}
	free_split(data->map);
	data->map = tmp;
	return (0);
}
