/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:05:18 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/26 18:20:59 by chonorat         ###   ########.fr       */
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
	while (x < (x_pos + (data->screen_res[1] >> 7)))
	{
		y = y_pos;
		while (y < (y_pos + (data->screen_res[1] >> 7)))
			mlx_pixel_put(data->mlx.mlx, data->mlx.window, x, y++, color);
		x++;
	}
	if (x - 10 == x_size * (data->screen_res[1] >> 7))
	{
		x_pos = 10;
		y_pos = y;
		if (y - 10 == y_size * (data->screen_res[1] >> 7))
		{
			y_pos = 10;
			x_pos = 10;
		}
	}
	else
		x_pos = x;
}

void	print_minimap(t_data *data, char **map)
{
	size_t	index[2];
	size_t	x_size;
	size_t	y_size;

	x_size = ft_strlen(map[0]);
	y_size = ft_arr_size(map);
	index[0] = 0;
	while (map[index[0]])
	{
		index[1] = 0;
		while (map[index[0]][index[1]])
		{
			if (map[index[0]][index[1]] == '1')
				print_square(data, (int)0xb3b3b3, x_size, y_size);
			else
				print_square(data, (int)0xffffff, x_size, y_size);
			index[1]++;
			print_player(data, 0.25 * (data->screen_res[1] >> 7), (int)0xff0000);
		}
		index[0]++;
	}
}
