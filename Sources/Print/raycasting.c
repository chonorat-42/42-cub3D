/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:10:01 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/28 17:46:42 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_plane(t_data *data)
{
	double	length;

	data->player.x_plane = data->player.y_dir;
	data->player.y_plane = -data->player.x_dir;
	length = sqrt(pow(data->player.x_plane, 2) + pow(data->player.y_plane, 2));
	data->player.x_plane /= length;
	data->player.y_plane /= length;
}

static void	get_step(t_data *data, struct s_raycast *data_rc)
{
	if (data_rc->x_ray < 0)
	{
		data_rc->x_step = -1;
		data_rc->side_dist_x = (data->player.x_pos - data_rc->x_map) * data_rc->delta_dist_x;
	}
	else
	{
		data_rc->x_step = 1;
		data_rc->side_dist_x = (data_rc->x_map + 1 - data->player.x_pos) * data_rc->delta_dist_x;
	}
	if (data_rc->y_ray < 0)
	{
		data_rc->y_step = -1;
		data_rc->side_dist_y = (data->player.y_pos - data_rc->y_map) * data_rc->delta_dist_y;
	}
	else
	{
		data_rc->y_step = 1;
		data_rc->side_dist_y = (data_rc->y_map + 1 - data->player.y_pos) * data_rc->delta_dist_y;
	}
}

static void	do_dda(t_data *data, struct s_raycast *data_rc)
{
	while (TRUE)
	{
		if (data_rc->side_dist_x < data_rc->delta_dist_y)
		{
			data_rc->side_dist_x += data_rc->delta_dist_x;
			data_rc->x_map += data_rc->x_step;
			data->player.side = 1;
		}
		else
		{
			data_rc->side_dist_y += data_rc->delta_dist_y;
			data_rc->y_map += data_rc->y_step;
			data->player.side = 0;
		}
		if (data->map[data_rc->y_map][data_rc->x_map] == '1')
			break;
	}
}

static void	print_column(t_data *data, struct s_raycast *data_rc, int x)
{
	int	column;
	int	start;
	int	end;
	int	temp;

	column = (int)(data->screen_res[1] / data_rc->distance);
	start = -column / 2 + data->screen_res[1] / 2;
	temp = start;
	while (temp >= 0)
		mlx_pixel_put(data->mlx.mlx, data->mlx.window, x, temp--, (int)0xffffff);
	end = column / 2 + data->screen_res[1] / 2;
	if (start < 0)
		start = 0;
	if (end >= data->screen_res[1])
		end = data->screen_res[1] - 1;
	while (start <= end)
		mlx_pixel_put(data->mlx.mlx, data->mlx.window, x, start++, (int)0xb3b3b3);
	while (start <= data->screen_res[1])
		mlx_pixel_put(data->mlx.mlx, data->mlx.window, x, start++, (int)0xffffff);
}

void	raycasting(t_data *data)
{
	struct s_raycast	data_rc;
	int					x;

	x = 0;
	init_raycast(&data_rc);
	init_plane(data);
	while (x < data->screen_res[0])
	{
		data_rc.x_cam = 2 * x / (double)data->screen_res[0] - 1;
		data_rc.x_ray = data->player.x_dir + data->player.x_plane * data_rc.x_cam;
		data_rc.y_ray = data->player.y_dir + data->player.y_plane * data_rc.x_cam;
		data_rc.x_map = (int)data->player.x_pos;
		data_rc.y_map = (int)data->player.y_pos;
		data_rc.delta_dist_x = sqrt(1 + pow(data_rc.y_ray, 2) / pow(data_rc.x_ray, 2));
		data_rc.delta_dist_y = sqrt(1 + pow(data_rc.x_ray, 2) / pow(data_rc.y_ray, 2));
		get_step(data, &data_rc);
		do_dda(data, &data_rc);
		if (!data->player.side)
			data_rc.distance = (data_rc.x_map - data->player.x_pos
				+ (1 - data_rc.x_step) / 2) / data_rc.x_ray;
		else
			data_rc.distance = (data_rc.y_map - data->player.y_pos
				+ (1 - data_rc.y_step) / 2) / data_rc.y_ray;
		print_column(data, &data_rc, x++);
	}
}
