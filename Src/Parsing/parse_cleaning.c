/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiogo-f <ddiogo-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:47:22 by darkless12        #+#    #+#             */
/*   Updated: 2025/07/21 15:40:23 by ddiogo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

void	free_data(t_parse *data)
{
	int	i;

	i = 0;
	if (data->n_face != NULL)
		free(data->n_face);
	if (data->s_face != NULL)
		free(data->s_face);
	if (data->e_face != NULL)
		free(data->e_face);
	if (data->w_face != NULL)
		free(data->n_face);
	while (data->map[i] != NULL)
		free(data->map[i++]);
	if (data->map != NULL)
		free(data->map);
	free(data);
}

int	parse_error(char *msg)
{
	ft_printf_fd(STDERR_FILENO, "Error\n");
	ft_printf_fd(STDERR_FILENO, "Cube3d: %s\n", msg);
	return (1);
}
