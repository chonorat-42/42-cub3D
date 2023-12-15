/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:38:22 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/15 12:58:58 by pgouasmi         ###   ########.fr       */
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
