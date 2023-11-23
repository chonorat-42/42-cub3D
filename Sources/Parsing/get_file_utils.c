/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:25:30 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/23 13:54:17 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_line(t_parser *parser, char *line)
{
	size_t	i;
	size_t	j;
	char	*id;

	i = 0;
	while (line[i] && ft_isws(line[i]))
		i++;
	j = i;
	while (line[i] && !ft_isws(line[i]))
		i++;
	id = ft_substr(line, j, i);
	if (!id)
		return (free_parser(parser), print_error(MALLOC, 0), exit(1));
	parse_id(parser, id, &i);
	free(id);
}

int	check_parsing_flags(t_textures textures, t_colors colors)
{
	if (textures.ea_flag != 1 || textures.no_flag != 1
		|| textures.so_flag != 1 || textures.we_flag != 1)
		return (0);
	if (colors.f_flag != 1 || colors.c_flag != 1)
		return (0);
	return (1);
}
