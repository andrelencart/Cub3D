#include "../../Inc/cube3d.h"

int	look_around(char **map, int ln, int cl)
{
	if (ln == 0 || cl == 0)
		return (1);
	if (!ft_strchr("01DX", map[ln][cl + 1]))
		return (1);
	if (!ft_strchr("01DX", map[ln][cl - 1]))
		return (1);
	if (!map[ln - 1] || (int)ft_strlen(map[ln - 1]) < cl)
		return (1);
	if (!ft_strchr("01DX", map[ln - 1][cl]))
		return (1);
	if (!map[ln + 1] || (int)ft_strlen(map[ln + 1]) < cl)
		return (1);
	if (!ft_strchr("01DX", map[ln + 1][cl]))
		return (1);
	return (0);
}

int	find_borders(t_parse *data)
{
	int	i;
	int	j;

	if (!data->player_dir)
		return (parse_error("Map has no starting position", 0));
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0' || data->map[i][j] == 'D')
			{
				if (look_around(data->map, i, j))
					return (map_error("Open tile at", i, j));
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	find_player_mons(t_parse *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (ft_strchr("NSEW", data->map[i][j]) && data->player_dir)
				return (map_error("Extra player in", i, j));
			else if (ft_strchr("NSEW", data->map[i][j]))
				assign_player_mons(data, i, j, 0);
			if (ft_strchr("M", data->map[i][j]) && data->enemy_x > -1)
				return (map_error("Extra monster in", i, j));
			else if (ft_strchr("M", data->map[i][j]))
				assign_player_mons(data, i, j, 1);
			j++;
		}
		i++;
	}
	return (find_borders(data));
}

int	validate_map(t_parse *data)
{
	int	i;
	int	j;
	int	nav;

	i = 0;
	nav = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][0] == '\n')
				return (map_error("Empty line in map", i, 0));
			if (!ft_strchr(" 01\nNSEWMDX", data->map[i][j]))
				return (map_error("Invalid char in map", i, j));
			if (ft_strchr("01NSEWMDX", data->map[i][j]))
				nav += 1;
			j++;
		}
		i++;
	}
	if (nav == 0)
		return (parse_error("Map is empty", 0));
	return (find_player_mons(data));
}

int	load_map(t_parse *data, int i)
{
	int		j;
	int		k;
	char	**tmp;

	i = find_map_edge(data->map, i, 1);
	j = find_map_edge(data->map, i, -1) + 1;
	tmp = ft_calloc(j - i + 1, sizeof(char *));
	if (!tmp)
		return (parse_error("Failed to allocate memory for map", 0));
	k = 0;
	while (i < j)
	{
		tmp[k] = ft_strdup(data->map[i]);
		if (!tmp[k])
			return (free_split(tmp), parse_error("Failed \
to allocate memory for a map line", 0));
		i++;
		k++;
	}
	free_split(data->map);
	data->map = tmp;
	return (validate_map(data));
}
