/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:10:01 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/29 01:08:34 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/*
static void	init_plane(t_data *data)
{
	double	length;

	data->player.x_plane = data->player.y_dir;
	data->player.y_plane = -data->player.x_dir;
	length = sqrt(pow(data->player.x_plane, 2) + pow(data->player.y_plane, 2));
	data->player.x_plane /= length;
	data->player.y_plane /= length;
}*/

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
		if (data_rc->side_dist_x < data_rc->side_dist_y)
		{
			data_rc->side_dist_x += data_rc->delta_dist_x;
			data_rc->x_map += data_rc->x_step;
			data->player.side = 0;
		}
		else
		{
			data_rc->side_dist_y += data_rc->delta_dist_y;
			data_rc->y_map += data_rc->y_step;
			data->player.side = 1;
		}
		if (data->map[data_rc->x_map][data_rc->y_map] == '1')
			break;
	}
}

static void	print_column(t_data *data, struct s_raycast *data_rc, int x)
{
	int	index;
	int	start;
	int	end;
	int	h_line;

	index = 0;
	h_line = (int)(data->screen_res[1] / data_rc->distance);
	start = -h_line / 2 + data->screen_res[1] / 2;
	if (start < 0)
		start = 0;
	end = data->screen_res[1] - start;
	while (index < start)
		mlx_pixel_put(data->mlx.mlx, data->mlx.window, x, index++, (int)0xffffff);
	while (index <= end)
		mlx_pixel_put(data->mlx.mlx, data->mlx.window, x, index++, (int)0xb3b3b3);
	index = end;
	while (index < data->screen_res[1])
		mlx_pixel_put(data->mlx.mlx, data->mlx.window, x, index++, (int)0xff0000);
}

void	raycasting(t_data *data)
{
	struct s_raycast	data_rc;
	int					x;

	x = 0;
	init_raycast(&data_rc);
	//init_plane(data);
	while (x < data->screen_res[0])
	{
		data_rc.x_cam = 2 * x / (double)data->screen_res[0] - 1;
		data_rc.x_ray = data->player.x_dir + data->player.x_plane * data_rc.x_cam;
		data_rc.y_ray = data->player.y_dir + data->player.y_plane * data_rc.x_cam;
		data_rc.x_map = (int)data->player.x_pos;
		data_rc.y_map = (int)data->player.y_pos;
		if (!data_rc.y_ray)
			data_rc.delta_dist_x = 0;
		else if (!data_rc.x_ray)
			data_rc.delta_dist_x = 1;
		else
			data_rc.delta_dist_x = sqrt(1 + data_rc.y_ray * data_rc.y_ray / data_rc.x_ray * data_rc.x_ray);
		if (!data_rc.x_ray)
			data_rc.delta_dist_y = 0;
		else if (!data_rc.y_ray)
			data_rc.delta_dist_y = 1;
		else
			data_rc.delta_dist_y = sqrt(1 + data_rc.x_ray * data_rc.x_ray / data_rc.y_ray * data_rc.y_ray);
		get_step(data, &data_rc);
		do_dda(data, &data_rc);
		if (!data->player.side)
			data_rc.distance = ((double)data_rc.x_map - data->player.x_pos
				+ (1 - (double)data_rc.x_step) / 2) / data_rc.x_ray;
		else
			data_rc.distance = ((double)data_rc.y_map - data->player.y_pos
				+ (1 - (double)data_rc.y_step) / 2) / data_rc.y_ray;
		print_column(data, &data_rc, x++);
	}
}
