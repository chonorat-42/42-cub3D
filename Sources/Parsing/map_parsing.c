/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:57:47 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/28 15:07:31 by pgouasmi         ###   ########.fr       */
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

void	map_parser(t_data *data, t_parser *parser)
{
	if (check_unknown_char(parser->map))
		return (free_data(data), exit(1));
	fill_map(data, parser);
	print_arr(data->map);
	if (check_borders(data->map))
		return (free_data(data), exit(1));
}
