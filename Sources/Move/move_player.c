/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:38:22 by chonorat          #+#    #+#             */
/*   Updated: 2024/01/04 12:49:36 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_data *data)
{
	if (data->player.move.sprint && !wall_hit(data,
			data->player.x_pos + (data->player.x_dir * S_PLAYER_SPEED) * 2,
			data->player.y_pos + (data->player.y_dir * S_PLAYER_SPEED) * 2))
	{
		data->player.x_pos += data->player.x_dir * S_PLAYER_SPEED;
		data->player.y_pos += data->player.y_dir * S_PLAYER_SPEED;
	}
	else if (!data->player.move.sprint && !wall_hit(data,
			data->player.x_pos + (data->player.x_dir * PLAYER_SPEED) * 2,
			data->player.y_pos + (data->player.y_dir * PLAYER_SPEED) * 2))
	{
		data->player.x_pos += data->player.x_dir * PLAYER_SPEED;
		data->player.y_pos += data->player.y_dir * PLAYER_SPEED;
	}
}

void	move_backward(t_data *data)
{
	if (data->player.move.sprint && !wall_hit(data,
			data->player.x_pos - (data->player.x_dir * S_PLAYER_SPEED) * 2,
			data->player.y_pos - (data->player.y_dir * S_PLAYER_SPEED) * 2))
	{
		data->player.x_pos -= data->player.x_dir * S_PLAYER_SPEED;
		data->player.y_pos -= data->player.y_dir * S_PLAYER_SPEED;
	}
	else if (!data->player.move.sprint && !wall_hit(data,
			data->player.x_pos - (data->player.x_dir * PLAYER_SPEED) * 2,
			data->player.y_pos - (data->player.y_dir * PLAYER_SPEED) * 2))
	{
		data->player.x_pos -= data->player.x_dir * PLAYER_SPEED;
		data->player.y_pos -= data->player.y_dir * PLAYER_SPEED;
	}
}

void	move_left(t_data *data)
{
	if (data->player.move.sprint && !wall_hit(data,
			data->player.x_pos + (data->player.y_dir * S_PLAYER_SPEED) * 2,
			data->player.y_pos - (data->player.x_dir * S_PLAYER_SPEED) * 2))
	{
		data->player.x_pos += data->player.y_dir * S_PLAYER_SPEED;
		data->player.y_pos -= data->player.x_dir * S_PLAYER_SPEED;
	}
	else if (!data->player.move.sprint && !wall_hit(data,
			data->player.x_pos + (data->player.y_dir * PLAYER_SPEED) * 2,
			data->player.y_pos - (data->player.x_dir * PLAYER_SPEED) * 2))
	{
		data->player.x_pos += data->player.y_dir * PLAYER_SPEED;
		data->player.y_pos -= data->player.x_dir * PLAYER_SPEED;
	}
}

void	move_right(t_data *data)
{
	if (data->player.move.sprint && !wall_hit(data,
			data->player.x_pos - (data->player.y_dir * S_PLAYER_SPEED) * 2,
			data->player.y_pos + (data->player.x_dir * S_PLAYER_SPEED) * 2))
	{
		data->player.x_pos -= data->player.y_dir * S_PLAYER_SPEED;
		data->player.y_pos += data->player.x_dir * S_PLAYER_SPEED;
	}
	else if (!data->player.move.sprint && !wall_hit(data,
			data->player.x_pos - (data->player.y_dir * PLAYER_SPEED) * 2,
			data->player.y_pos + (data->player.x_dir * PLAYER_SPEED) * 2))
	{
		data->player.x_pos -= data->player.y_dir * PLAYER_SPEED;
		data->player.y_pos += data->player.x_dir * PLAYER_SPEED;
	}
}
