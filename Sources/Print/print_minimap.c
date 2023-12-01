/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:05:18 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/01 15:21:42 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	print_square(t_data *data, int color, size_t x_size, size_t y_size)
{
	static size_t	y_pos = 10;
	static size_t	x_pos = 10;
	size_t			y;
	size_t			x;

	x = x_pos;
	y = 0;
	while (x < (x_pos + data->minimap_ratio))
	{
		y = y_pos;
		while (y < (y_pos + data->minimap_ratio))
			pixel_to_frame(data, x, y++, color);
		x++;
	}
	if (x - 10 == x_size * data->minimap_ratio)
	{
		x_pos = 10;
		y_pos = y;
		if (y - 10 == y_size * data->minimap_ratio)
		{
			y_pos = 10;
			x_pos = 10;
		}
	}
	else
		x_pos = x;
}

void	print_minimap(t_data *data)
{
	size_t	index[2];
	size_t	x_size;
	size_t	y_size;

	x_size = ft_strlen(data->map[0]);
	y_size = ft_arr_size(data->map);
	index[0] = 0;
	while (data->map[index[0]])
	{
		index[1] = 0;
		while (data->map[index[0]][index[1]])
		{
			if (data->map[index[0]][index[1]] == '1')
				print_square(data, (int)0xb3b3b3, x_size, y_size);
			else if (data->map[index[0]][index[1]] == '0')
				print_square(data, (int)0xffffff, x_size, y_size);
			else
				print_square(data, -1, x_size, y_size);
			index[1]++;
			print_player(data, 0.25 * data->minimap_ratio, (int)0xff0000);
		}
		index[0]++;
	}
}
