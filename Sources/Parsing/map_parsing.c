/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:57:47 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/27 14:39:51 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_player_position(t_data *data)
{
	long long	j;
	long long	i;
	int			found;

	j = -1;
	found = 0;
	while (data->map[++j])
	{
		i = -1;
		while (data->map[j][++i])
		{
			if (ft_ischarinset(data->map[j][i], "NSEW"))
			{
				if (!found)
				{
					data->player.x_pos = (double)j + 0.5;
					data->player.y_pos = (double)i + 0.5;
					found++;
				}
				else
					return (print_error(PARSING, DPP), free_data(data), exit(1));
			}
		}
	}
	if (found == 1)
		return ;
	return (print_error(PARSING, NOP), free_data(data), exit(1));
}

void	map_parser(t_data *data, t_parser *parser)
{
	(void)parser;
	print_arr(data->map);
	get_player_position(data);
}
