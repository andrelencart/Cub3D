/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darkless12 <darkless12@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:47:22 by darkless12        #+#    #+#             */
/*   Updated: 2025/07/18 18:48:09 by darkless12       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/cube3d.h"

int	parse_error(char *msg)
{
	ft_printf_fd(STDERR_FILENO, "Error\n");
	ft_printf_fd(STDERR_FILENO, "Cube3d: %s\n", msg);
	return (1);
}
