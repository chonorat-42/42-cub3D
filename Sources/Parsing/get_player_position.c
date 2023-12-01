/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_position.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:04:45 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/01 12:15:30 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	player_position_found(t_data *data, int *found,
	long long i, long long j)
{
	if (!*found)
	{
		get_player_dir(data, i, j);
		data->player.x_pos = (double)i + 0.5;
		data->player.y_pos = (double)j + 0.5;
		(*found)++;
		return (0);
	}
	else
		return (print_error(PARSING, DPP), free_data(data), 1);
}

void	get_player_position(t_data *data)
{
	long long	j;
	long long	i;
	int			found;

	j = -1;
	found = 0;
	while (data->parser.map[++j])
	{
		i = -1;
		while (data->parser.map[j][++i])
		{
			if (ft_ischarinset(data->parser.map[j][i], "NSEW"))
			{
				if (player_position_found(data, &found, i, j))
					exit(1);
			}
		}
	}
	if (found == 1)
		return ;
	return (print_error(PARSING, NOP), free_data(data), exit(1));
}
