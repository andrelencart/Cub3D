/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parse.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiogo-f <ddiogo-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:41:10 by darkless12        #+#    #+#             */
/*   Updated: 2025/07/21 14:17:12 by ddiogo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_PARSE_H
# define CUBE_PARSE_H

# include <errno.h>

typedef struct	s_parse
{
	char	*n_face;
	char	*s_face;
	char	*e_face;
	char	*w_face;
	char	**map;
}	t_parse;

//parse_cleaning.c
int		parse_error(char *msg);
void	free_data(t_parse *data);

//cube_checker.c
int	parse_check_fname(char *fname, t_parse *data);

#endif
