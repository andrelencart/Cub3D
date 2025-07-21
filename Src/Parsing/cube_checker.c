/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiogo-f <ddiogo-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:46:50 by darkless12        #+#    #+#             */
/*   Updated: 2025/07/21 14:20:32 by ddiogo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

//copying fname to data->map.
int	get_data(char *fname, t_parse *data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	line = ft_strjoin("maps/", fname);
	if (!line)
		return (free_data(data), parse_error("Failed to allocate *line"));
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (free_data(data), free(line), parse_error(strerror(errno)));
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		data->map[i++] = line;
	}
	free(line);
	close(fd);
	return (0);
}

//Verify that fname exists, can be read and allocating memory to **map
int	find_file(char *fname, t_parse *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	line = ft_strjoin("maps/", fname);
	if (!line)
		return (free(data), parse_error("Failed to allocate *line"));
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (free(data), free(line), parse_error(strerror(errno)));
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	data->map = ft_calloc(i + 1, sizeof(char *));
	if (!data->map)
		return (free(data), parse_error("Failed to allocate data->map"));
	return (get_data(fname, data));
}

//verify that fname is .cub and has a min size
int	parse_check_fname(char *fname, t_parse *data)
{
	int	len;

	len = ft_strlen(fname);
	if (ft_strncmp(&fname[len - 4], ".cub", 4) || len < 5)
		return (free(data), parse_error("File name is not valid"));
	return (find_file(fname, data));
}
