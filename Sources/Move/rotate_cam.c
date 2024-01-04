/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:36:37 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/17 14:22:20 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	mouse_rotate_cam(t_data *data)
{
	int		mouse_x;
	double	mouse_move;

	if (!data->reset_mouse)
	{
		mouse_x = data->mouse_pos[0];
		mlx_mouse_get_pos(data->mlx.mlx, data->mlx.window,
			&data->mouse_pos[0], &data->mouse_pos[1]);
		mouse_move = (data->mouse_pos[0] - mouse_x) * data->mouse_sensibility;
		data->player.angle += mouse_move;
		data->player.x_dir = cos(data->player.angle);
		data->player.y_dir = sin(data->player.angle);
		data->player.x_plane = cos(data->player.angle + M_PI_2);
		data->player.y_plane = sin(data->player.angle + M_PI_2);
	}
	data->reset_mouse = 0;
	if (data->mouse_pos[0] <= 0 || data->mouse_pos[0] >= data->screen_res[0]
		|| data->mouse_pos[1] <= 0 || data->mouse_pos[1] >= data->screen_res[1])
	{
		mlx_mouse_move(data->mlx.mlx, data->mlx.window,
			data->screen_res[0] >> 1, data->screen_res[1] >> 1);
		mlx_mouse_get_pos(data->mlx.mlx, data->mlx.window,
			&data->mouse_pos[0], &data->mouse_pos[1]);
		data->reset_mouse = 1;
	}
}

void	rotate_cam(t_data *data)
{
	if (data->mouse_enabled)
		mouse_rotate_cam(data);
	if (data->player.move.l_cam)
	{
		data->player.angle -= CAM_SPEED;
		data->player.x_dir = cos(data->player.angle);
		data->player.y_dir = sin(data->player.angle);
		data->player.x_plane = cos(data->player.angle + M_PI_2);
		data->player.y_plane = sin(data->player.angle + M_PI_2);
	}
	if (data->player.move.r_cam)
	{
		data->player.angle += CAM_SPEED;
		data->player.x_dir = cos(data->player.angle);
		data->player.y_dir = sin(data->player.angle);
		data->player.x_plane = cos(data->player.angle + M_PI_2);
		data->player.y_plane = sin(data->player.angle + M_PI_2);
	}
}
