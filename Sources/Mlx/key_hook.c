/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:59:22 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/04 16:22:13 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == MAJ)
		data->player.move.sprint = 1;
	else if (keycode == L_MOVE)
		data->player.move.l_move = 1;
	else if (keycode == R_MOVE)
		data->player.move.r_move = 1;
	else if (keycode == F_MOVE)
		data->player.move.f_move = 1;
	else if (keycode == B_MOVE)
		data->player.move.b_move = 1;
	else if (keycode == L_CAM)
		data->player.move.l_cam = 1;
	else if (keycode == R_CAM)
		data->player.move.r_cam = 1;
	else if (keycode == ESC)
		exit_prog(data);
	else if (keycode == TAB)
	{
		data->mouse_enabled++;
		data->mouse_enabled %= 2;
	}
	return (1);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == MAJ)
		data->player.move.sprint = 0;
	else if (keycode == L_MOVE)
		data->player.move.l_move = 0;
	else if (keycode == R_MOVE)
		data->player.move.r_move = 0;
	else if (keycode == F_MOVE)
		data->player.move.f_move = 0;
	else if (keycode == B_MOVE)
		data->player.move.b_move = 0;
	else if (keycode == L_CAM)
		data->player.move.l_cam = 0;
	else if (keycode == R_CAM)
		data->player.move.r_cam = 0;
	return (1);
}