/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darkless12 <darkless12@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:46:50 by darkless12        #+#    #+#             */
/*   Updated: 2025/07/18 19:07:12 by darkless12       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../Inc/cube3d.h"

//verifica se o nome termina em .cub
int	parse_check_fname(char *fname)
{
	char	*ext;
	int		len;

	ext = ".cub";
	len = ft_strlen(fname);
	if (ft_strncmp(&fname[len - 4], ext, 4) || len < 5)
		return (parse_error("Wrong file extension"));
	return (0);
}
