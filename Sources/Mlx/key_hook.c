/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:59:22 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/13 13:37:20 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_pause(t_data *data)
{
	data->mouse_enabled++;
	data->mouse_enabled %= 2;
	data->pause_menu.in_pause++;
	data->pause_menu.in_pause %= 2;
	if (data->pause_menu.in_pause)
		mlx_mouse_show(data->mlx.mlx, data->mlx.window);
	else if (!data->pause_menu.in_pause)
		mlx_mouse_hide(data->mlx.mlx, data->mlx.window);
}

int	mouse_hook(int mousekey, t_data *data)
{
	(void)data;
	printf("mousekey[%d]\n", mousekey);
	return (1);
}

int	key_press(int keycode, t_data *data)
{
	printf("keycode[%d]\n", keycode);
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
	else if (keycode == F1)
		set_pause(data);
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