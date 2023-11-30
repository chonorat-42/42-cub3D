/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:45:39 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/30 00:53:38 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_player_dir(t_data *data, long long i, long long j)
{
	if (data->parser.map[j][i] == 'N')
	{
		data->player.x_dir = 0.0;
		data->player.y_dir = -1.0;
		data->player.x_plane = 1.0;
		data->player.y_plane = 0.0;
	}
	else if (data->parser.map[j][i] == 'S')
	{
		data->player.x_dir = 0.0;
		data->player.y_dir = 1.0;
		data->player.x_plane = -1.0;
		data->player.y_plane = 0.0;
	}
	else if (data->parser.map[j][i] == 'E')
	{
		data->player.x_dir = 1.0;
		data->player.y_dir = 0.0;
		data->player.x_plane = 0.0;
		data->player.y_plane = 1.0;
	}
	else if (data->parser.map[j][i] == 'W')
	{
		data->player.x_dir = -1.0;
		data->player.y_dir = 0.0;
		data->player.x_plane = 0.0;
		data->player.y_plane = -1.0;
	}
}
