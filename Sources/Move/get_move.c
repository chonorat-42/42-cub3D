/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 22:48:06 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/01 14:01:18 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	wall_hit(t_data *data, int pos_x, int pos_y)
{
	if (data->map[pos_y][pos_x] && data->map[pos_y][pos_x] == '1')
		return (TRUE);
	return (FALSE);
}

void	get_move(t_data *data)
{
	rotate_cam(data);
	if (data->player.move.f_move)
		move_forward(data);
	if (data->player.move.b_move)
		move_backward(data);
	if (data->player.move.l_move)
		move_left(data);
	if (data->player.move.r_move)
		move_right(data);
}
