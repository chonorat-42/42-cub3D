/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:05:18 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/24 17:58:05 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	print_square(t_data *data, int color, size_t size)
{
	static size_t	y_pos = 0;
	static size_t	x_pos = 0;
	size_t			y;
	size_t			x;

	x = x_pos;
	while (x < (x_pos + (data->screen_res[1] >> 7)))
	{
		y = y_pos;
		while (y < (y_pos + (data->screen_res[1] >> 7)))
			mlx_pixel_put(data->mlx.mlx, data->mlx.window, x, y++, color);
		x++;
	}
	if (x == size * (data->screen_res[1] >> 7))
	{
		x_pos = 0;
		y_pos = y;
	}
	else
		x_pos = x;
}

void	print_minimap(t_data *data, char **map)
{
	size_t	index[2];
	size_t	size;

	size = ft_strlen(map[0]);
	index[0] = 0;
	while (map[index[0]])
	{
		index[1] = 0;
		while (map[index[0]][index[1]])
		{
			if (map[index[0]][index[1]] == '1')
				print_square(data, (int)0xb3b3b3, size);
			else
				print_square(data, (int)0xffffff, size);
			index[1]++;
		}
		index[0]++;
	}
}