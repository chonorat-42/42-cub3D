/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:36:37 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/01 13:58:00 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_cam(t_data *data)
{
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
