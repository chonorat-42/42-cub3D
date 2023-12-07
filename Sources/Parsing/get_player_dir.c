/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:45:39 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/01 12:41:05 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_player_dir(t_data *data, long long i, long long j)
{
	if (data->parser.map[j][i] == 'N')
	{
		data->player.angle = -M_PI_2;
		data->player.x_dir = cos(data->player.angle);
		data->player.y_dir = sin(data->player.angle);
		data->player.x_plane = cos(data->player.angle + M_PI_2);
		data->player.y_plane = sin(data->player.angle + M_PI_2);
	}
	else if (data->parser.map[j][i] == 'S')
	{
		data->player.angle = M_PI_2;
		data->player.x_dir = cos(data->player.angle);
		data->player.y_dir = sin(data->player.angle);
		data->player.x_plane = cos(data->player.angle + M_PI_2);
		data->player.y_plane = sin(data->player.angle + M_PI_2);
	}
	else if (data->parser.map[j][i] == 'E')
	{
		data->player.angle = 0.0;
		data->player.x_dir = cos(data->player.angle);
		data->player.y_dir = sin(data->player.angle);
		data->player.x_plane = cos(data->player.angle + M_PI_2);
		data->player.y_plane = sin(data->player.angle + M_PI_2);
	}
	else if (data->parser.map[j][i] == 'W')
	{
		data->player.angle = M_PI;
		data->player.x_dir = cos(data->player.angle);
		data->player.y_dir = sin(data->player.angle);
		data->player.x_plane = cos(data->player.angle + M_PI_2);
		data->player.y_plane = sin(data->player.angle + M_PI_2);
	}
}
