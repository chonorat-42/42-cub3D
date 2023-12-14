/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:23:28 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/14 18:00:03 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_color_sprite(t_data *data, int x, int y)
{
	int	color;
	int	index;

	data->ghost.addr = mlx_get_data_addr(data->ghost.img, &data->ghost.bpp,
			&data->ghost.line_length, &data->ghost.endian);
	index = (y * data->ghost.line_length) + (x * (data->ghost.bpp / 8));
	color = (*(unsigned int *)(data->ghost.addr + index));
	return (color);
}

static void	init_sprite(t_data *data, struct s_raycast *data_rc)
{
	data_rc->ennemy.distance = (data->player.x_pos - data->ennemy.d_pos[1])
		* (data->player.x_pos - data->ennemy.d_pos[1]) + (data->player.y_pos
			- data->ennemy.d_pos[0]) * (data->player.y_pos
			- data->ennemy.d_pos[0]);
	data_rc->ennemy.sprite_x = data->ennemy.d_pos[1] - data->player.x_pos;
	data_rc->ennemy.sprite_y = data->ennemy.d_pos[0] - data->player.y_pos;
	data_rc->ennemy.inv_det = 1.0 / (data->player.x_plane * data->player.y_dir
			- data->player.y_plane * data->player.x_dir);
	data_rc->ennemy.x_transform = data_rc->ennemy.inv_det * (data->player.y_dir
			* data_rc->ennemy.sprite_x - data->player.x_dir
			* data_rc->ennemy.sprite_y);
	data_rc->ennemy.y_transform = data_rc->ennemy.inv_det
		* (-data->player.y_plane * data_rc->ennemy.sprite_x
			+ data->player.x_plane * data_rc->ennemy.sprite_y);
	data_rc->ennemy.screen_x = (int)(data_rc->width * 0.5)
		* (1 + data_rc->ennemy.x_transform / data_rc->ennemy.y_transform);
	data_rc->ennemy.sprite_h = abs((int)(data_rc->height
				/ data_rc->ennemy.y_transform));
}

static void	sprite_to_frame(t_data *data, struct s_raycast *data_rc, int index)
{
	if (data_rc->ennemy.color != (int)0x0)
	{
		data_rc->ennemy.color = get_fog(data_rc->ennemy.color,
				data->fog_density, data->zbuffer[index]);
		pixel_to_frame(data, index, data_rc->ennemy.y, data_rc->ennemy.color);
	}
}

static void	print_sprite(t_data *data, struct s_raycast *data_rc, int index)
{
	while (index < data_rc->ennemy.end_x)
	{
		data_rc->ennemy.tex_x = (int)(256 * (index - (-data_rc->ennemy.sprite_w
						/ 2 + data_rc->ennemy.screen_x)) * 256
				/ data_rc->ennemy.sprite_w) / 256;
		if (data_rc->ennemy.y_transform > 0 && index >= 0
			&& index < data_rc->width
			&& data_rc->ennemy.y_transform < data->zbuffer[index])
		{
			data_rc->ennemy.y = data_rc->ennemy.start_y;
			while (data_rc->ennemy.y < data_rc->ennemy.end_y)
			{
				data_rc->ennemy.d = (data_rc->ennemy.y) * 256
					- data_rc->height * 128
					+ data_rc->ennemy.sprite_h * 128;
				data_rc->ennemy.tex_y = ((data_rc->ennemy.d * 256)
						/ data_rc->ennemy.sprite_h) / 256;
				data_rc->ennemy.color = get_color_sprite(data,
						data_rc->ennemy.tex_x, data_rc->ennemy.tex_y);
				data_rc->ennemy.y++;
				sprite_to_frame(data, data_rc, index);
			}
		}
		index++;
	}
}

void	get_sprite(t_data *data, struct s_raycast *data_rc)
{
	int	index;

	index = 0;
	init_sprite(data, data_rc);
	data_rc->ennemy.start_y = -data_rc->ennemy.sprite_h * 0.5 + data_rc->height
		* 0.5;
	if (data_rc->ennemy.start_y < 0)
		data_rc->ennemy.start_y = 0;
	data_rc->ennemy.end_y = data_rc->ennemy.sprite_h * 0.5 + data_rc->height
		* 0.5;
	if (data_rc->ennemy.end_y >= data_rc->height)
		data_rc->ennemy.end_y = data_rc->height;
	data_rc->ennemy.sprite_w = abs((int)(data_rc->height
				/ data_rc->ennemy.y_transform));
	data_rc->ennemy.start_x = -data_rc->ennemy.sprite_w
		* 0.5 + data_rc->ennemy.screen_x;
	if (data_rc->ennemy.start_x < 0)
		data_rc->ennemy.start_x = 0;
	data_rc->ennemy.end_x = data_rc->ennemy.sprite_w * 0.5
		+ data_rc->ennemy.screen_x;
	if (data_rc->ennemy.end_x >= data_rc->width)
		data_rc->ennemy.end_x = data_rc->width;
	index = data_rc->ennemy.start_x;
	print_sprite(data, data_rc, index);
}
