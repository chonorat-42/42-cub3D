/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:07:13 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/17 16:15:32 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	end_menu(t_data *data)
{
	if (data->pause_menu.on_exit)
		exit_prog(data);
	if (data->pause_menu.on_retry)
	{
		data->pause_menu.in_escape = 0;
		data->pause_menu.in_death = 0;
		data->player.x_pos = data->saved_data.x_pos;
		data->player.y_pos = data->saved_data.y_pos;
		data->player.angle = data->saved_data.angle;
		data->player.x_dir = cos(data->player.angle);
		data->player.y_dir = sin(data->player.angle);
		data->player.x_plane = cos(data->player.angle + M_PI_2);
		data->player.y_plane = sin(data->player.angle + M_PI_2);
		data->ennemy.pos[0] = data->saved_data.ennemy_pos[0];
		data->ennemy.pos[1] = data->saved_data.ennemy_pos[1];
		data->ennemy.d_pos[0] = data->ennemy.pos[0] + 0.5;
		data->ennemy.d_pos[1] = data->ennemy.pos[1] + 0.5;
		data->ennemy.target[0] = data->player.y_pos;
		data->ennemy.target[1] = data->player.x_pos;
		data->pause_menu.in_pause = 0;
		data->pause_menu.in_options = 0;
		init_pause(data);
		mlx_mouse_hide(data->mlx.mlx, data->mlx.window);
	}
}

int	mouse_hook(int mousekey, int x, int y, t_data *data)
{
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
	if (data->pause_menu.in_death || data->pause_menu.in_escape)
		end_menu(data);
	return (1);
}
