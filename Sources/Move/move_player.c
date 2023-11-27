/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 22:48:06 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/27 17:21:44 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	wall_hit(t_data *data, int pos_x, int pos_y)
{
	if (data->map[pos_y][pos_x] && data->map[pos_y][pos_x] == '1')
		return (TRUE);
	return (FALSE);
}

static void	move_lr(t_data *data)
{
	if (data->player.move.l_move)
	{
		if (data->player.move.sprint && !wall_hit(data, data->player.x_pos - 0.4, data->player.y_pos))
			data->player.x_pos -= 0.4;
		else if (!data->player.move.sprint && !wall_hit(data, data->player.x_pos - 0.2, data->player.y_pos))
			data->player.x_pos -= 0.2;
	}
	if (data->player.move.r_move)
	{
		if (data->player.move.sprint && !wall_hit(data, data->player.x_pos + 0.4, data->player.y_pos))
			data->player.x_pos += 0.4;
		else if (!data->player.move.sprint && !wall_hit(data, data->player.x_pos + 0.2, data->player.y_pos))
			data->player.x_pos += 0.2;
	}
}

void	move_player(t_data *data)
{
	move_lr(data);
	if (data->player.move.f_move)
	{
		if (data->player.move.sprint && !wall_hit(data, data->player.x_pos, data->player.y_pos - 0.4))
			data->player.y_pos -= 0.4;
		else if (!data->player.move.sprint && !wall_hit(data, data->player.x_pos, data->player.y_pos - 0.2))
			data->player.y_pos -= 0.2;
	}
	if (data->player.move.b_move)
	{
		if (data->player.move.sprint && !wall_hit(data, data->player.x_pos,
			data->player.y_pos + 0.4))
			data->player.y_pos += 0.4;
		else if (!data->player.move.sprint && !wall_hit(data, data->player.x_pos, data->player.y_pos + 0.2))
			data->player.y_pos += 0.2;
	}
}