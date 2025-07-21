/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiogo-f <ddiogo-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:52:52 by andcarva          #+#    #+#             */
/*   Updated: 2025/07/21 14:17:45 by ddiogo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/cube3d.h"
#include "../../Inc/cube_parse.h"

int	main(int ac, char **av)
{
	t_parse	*data;

	if (ac != 2 || !av)
		return (parse_error("Wrong number of arguments"));
	data = ft_calloc(1, sizeof(t_parse));
	if (!data)
		return (parse_error("Failed to allocate *data"));
	if (parse_check_fname(av[1], data))
		return(1);
	return (0);
}