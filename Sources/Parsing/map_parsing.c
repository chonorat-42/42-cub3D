/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:57:47 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/01 12:21:53 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_unknown_char(char **map)
{
	size_t	j;

	j = 0;
	while (map[j])
	{
		if (!ft_isstronlyset(map[j], "01NSWE "))
			return (print_error(PARSING, UNKCHAR), 1);
		j++;
	}
	return (0);
}

int	map_has_empty_line(char **map)
{
	size_t	j;

	j = 0;
	while (map[j])
	{
		if (ft_isstrws(map[j]))
			return (print_error(PARSING, EMPTYL), 1);
		j++;
	}
	return (0);
}

void	map_parser(t_data *data, t_parser *parser)
{
	if (map_has_empty_line(parser->map))
		return (free_data(data), exit(1));
	if (check_unknown_char(parser->map))
		return (free_data(data), exit(1));
	fill_map(data, parser);
	if (check_borders(data->map))
		return (free_data(data), exit(1));
	if (is_map_separated(data, data->map))
		return (free_data(data), exit(1));
}
