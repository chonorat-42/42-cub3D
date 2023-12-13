/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:59:22 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/13 17:27:05 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_pause(t_data *data)
{
	data->mouse_enabled++;
	data->mouse_enabled %= 2;
	data->pause_menu.in_pause++;
	data->pause_menu.in_pause %= 2;
	data->pause_menu.in_options = 0;
	if (data->pause_menu.in_pause)
		mlx_mouse_show(data->mlx.mlx, data->mlx.window);
	else if (!data->pause_menu.in_pause)
		mlx_mouse_hide(data->mlx.mlx, data->mlx.window);
}

static void	change_difficulty(t_data *data)
{
	if (data->difficulty == IMPOSSIBLE)
		data->difficulty = EASY;
	else
		data->difficulty++;
	if (data->difficulty == EASY)
		data->ennemy.speed = 0.0125;
	else if (data->difficulty == NORMAL)
		data->ennemy.speed = 0.0250;
	else if (data->difficulty == HARD)
		data->ennemy.speed = 0.0375;
	else if (data->difficulty == IMPOSSIBLE)
		data->ennemy.speed = 0.05;
}

static void	change_fog(t_data *data)
{
	if (data->fog_setting == VERY_HIGH)
		data->fog_setting = LOW;
	else
		data->fog_setting++;
	if (data->fog_setting == LOW)
		data->fog_density = 0.5;
	else if (data->fog_setting == MEDIUM)
		data->fog_density = 1.0;
	else if (data->fog_setting == HIGH)
		data->fog_density = 1.5;
	else if (data->fog_setting == VERY_HIGH)
		data->fog_density = 2.0;
}

void	options_hook(t_data *data)
{
	if (data->pause_menu.on_back)
		data->pause_menu.in_options = 0;
	if (data->pause_menu.on_difficulty)
		change_difficulty(data);
	if (data->pause_menu.on_fog)
		change_fog(data);
}

int	mouse_hook(int mousekey, int x, int y, t_data *data)
{
	printf("mousekey[%d]\n", mousekey);
	(void)x;
	(void)y;
	if (data->pause_menu.in_pause && mousekey == L_MOUSE
		&& !data->pause_menu.in_options)
	{
		if (data->pause_menu.on_resume)
		{
			data->pause_menu.in_options = 0;
			data->pause_menu.in_pause = 0;
			data->mouse_enabled = 1;
			mlx_mouse_hide(data->mlx.mlx, data->mlx.window);
		}
		if (data->pause_menu.on_options)
			data->pause_menu.in_options = 1;
		if (data->pause_menu.on_exit)
			exit_prog(data);
	}
	if (data->pause_menu.in_options)
		options_hook(data);
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