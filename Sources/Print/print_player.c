/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:51:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/24 18:00:34 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_player(t_data *data)
{
	size_t	pixel[2];

	pixel[0] = data->player.y_pos;
	pixel[1] = data->player.x_pos;

	mlx_pixel_put(data->mlx.mlx, data->mlx.window,
		(int)data->player.x_pos, (int)data->player.y_pos, (int)0xff0000);
}