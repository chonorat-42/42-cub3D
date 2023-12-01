/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:51:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/01 15:22:38 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_player(t_data *data, double radius, int color)
{
	size_t	pixel[2];
	double	player_x;
	double	player_y;

	player_x = (data->player.x_pos * data->minimap_ratio) + 10;
	player_y = (data->player.y_pos * data->minimap_ratio) + 10;
	pixel[0] = player_x - radius;
	while (pixel[0] <= player_x + radius)
	{
		pixel[1] = player_y - radius;
		while (pixel[1] <= player_y + radius)
		{
			if (pow(pixel[0] - player_x, 2)
				+ pow(pixel[1] - player_y, 2) <= pow(radius, 2))
				pixel_to_frame(data, pixel[0], pixel[1], color);
			pixel[1]++;
		}
		pixel[0]++;
	}
}
