/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:10:01 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/01 15:18:56 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_value(t_data *data, struct s_raycast *data_rc, int x)
{
	data_rc->x_cam = (2 * x / (double)data_rc->width) - 1;
	data_rc->xpos_ray = data->player.x_pos;
	data_rc->ypos_ray = data->player.y_pos;
	data_rc->xdir_ray = data->player.x_dir + (data->player.x_plane * data_rc->x_cam);
	data_rc->ydir_ray = data->player.y_dir + (data->player.y_plane * data_rc->x_cam);
	data_rc->x_map = (int)data_rc->xpos_ray;
	data_rc->y_map = (int)data_rc->ypos_ray;
	data_rc->delta_dist_x = sqrtf(1 + (data_rc->ydir_ray * data_rc->ydir_ray) / (data_rc->xdir_ray * data_rc->xdir_ray));
	data_rc->delta_dist_y = sqrtf(1 + (data_rc->xdir_ray * data_rc->xdir_ray) / (data_rc->ydir_ray * data_rc->ydir_ray));
	data_rc->wall_hit = 0;
}

static void	get_initial_dist(struct s_raycast *data_rc)
{
	if (data_rc->xdir_ray < 0)
	{
		data_rc->x_step = -1;
		data_rc->side_dist_x = (data_rc->xpos_ray - data_rc->x_map) * data_rc->delta_dist_x;
	}
	else
	{
		data_rc->x_step = 1;
		data_rc->side_dist_x = (data_rc->x_map + 1.0 - data_rc->xpos_ray) * data_rc->delta_dist_x;
	}
	if (data_rc->ydir_ray < 0)
	{
		data_rc->y_step = -1;
		data_rc->side_dist_y = (data_rc->ypos_ray - data_rc->y_map) * data_rc->delta_dist_y;
	}
	else
	{
		data_rc->y_step = 1;
		data_rc->side_dist_y = (data_rc->y_map + 1.0 - data_rc->ypos_ray) * data_rc->delta_dist_y;
	}
}

static void	get_wall(t_data *data, struct s_raycast *data_rc)
{
	while (!data_rc->wall_hit)
	{
		if (data_rc->side_dist_x < data_rc->side_dist_y)
		{
			data_rc->side_dist_x += data_rc->delta_dist_x;
			data_rc->x_map += data_rc->x_step;
			data_rc->wall_side = 0;
		}
		else
		{
			data_rc->side_dist_y += data_rc->delta_dist_y;
			data_rc->y_map += data_rc->y_step;
			data_rc->wall_side = 1;
		}
		if (data->map[data_rc->y_map][data_rc->x_map] == '1')
			data_rc->wall_hit = 1;
	}
	if (data_rc->wall_side == 0)
		data_rc->pwall_dist = fabs(((double)data_rc->x_map - data_rc->xpos_ray + (1 - (double)data_rc->x_step) / 2) / data_rc->xdir_ray);
	else
		data_rc->pwall_dist = fabs(((double)data_rc->y_map - data_rc->ypos_ray + (1 - (double)data_rc->y_step) / 2) / data_rc->ydir_ray);
}

static void	print_column(t_data *data, struct s_raycast *data_rc, int x)
{
	int	h_line;
	int	start;
	int	end;
	int	color;
	int	y;

	h_line = fabs((data_rc->height / data_rc->pwall_dist));
	start = -h_line / 2 + data_rc->height / 2;
	end = h_line / 2 + data_rc->height / 2;
	if (start < 0)
		start = 0;
	if (end >= data_rc->height)
		end = data_rc->height - 1;
	y = start;
	while (y < end)
	{
		color = (int)0xf2f2f2;
		if (data_rc->wall_side == 1)
			color = (int)0xCCCCCC;
		pixel_to_frame(data, x, y++, color);
	}
	if (end < 0)
		end = data_rc->height;
	y = end;
	while (y < data_rc->height)
	{
		pixel_to_frame(data, x, y, (int)0x8b0000);
		pixel_to_frame(data, x, data_rc->height - y++ - 1, (int)0x8b0000);
	}
}

void	raycasting(t_data *data, struct s_raycast *data_rc)
{
	int	x;

	x = 0;
	data_rc->height = data->screen_res[1];
	data_rc->width = data->screen_res[0];
	while (x <= data_rc->width)
	{
		get_value(data, data_rc, x);
		get_initial_dist(data_rc);
		get_wall(data, data_rc);
		print_column(data, data_rc, x);
		x++;
	}
}
