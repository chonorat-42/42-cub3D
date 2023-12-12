/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:10:01 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/12 12:32:21 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_value(t_data *data, struct s_raycast *data_rc, int x)
{
	data_rc->x_cam = (2 * x / (double)data_rc->width) - 1;
	data_rc->xpos_ray = data->player.x_pos;
	data_rc->ypos_ray = data->player.y_pos;
	data_rc->xdir_ray = data->player.x_dir + (data->player.x_plane
			* data_rc->x_cam);
	data_rc->ydir_ray = data->player.y_dir + (data->player.y_plane
			* data_rc->x_cam);
	data_rc->x_map = (int)data_rc->xpos_ray;
	data_rc->y_map = (int)data_rc->ypos_ray;
	data_rc->delta_dist_x = sqrtf(1 + (data_rc->ydir_ray * data_rc->ydir_ray)
			/ (data_rc->xdir_ray * data_rc->xdir_ray));
	data_rc->delta_dist_y = sqrtf(1 + (data_rc->xdir_ray * data_rc->xdir_ray)
			/ (data_rc->ydir_ray * data_rc->ydir_ray));
	data_rc->wall_hit = 0;
}

static void	get_initial_dist(struct s_raycast *data_rc)
{
	if (data_rc->xdir_ray < 0)
	{
		data_rc->x_step = -1;
		data_rc->side_dist_x = (data_rc->xpos_ray - data_rc->x_map)
			* data_rc->delta_dist_x;
	}
	else
	{
		data_rc->x_step = 1;
		data_rc->side_dist_x = (data_rc->x_map + 1.0 - data_rc->xpos_ray)
			* data_rc->delta_dist_x;
	}
	if (data_rc->ydir_ray < 0)
	{
		data_rc->y_step = -1;
		data_rc->side_dist_y = (data_rc->ypos_ray - data_rc->y_map)
			* data_rc->delta_dist_y;
	}
	else
	{
		data_rc->y_step = 1;
		data_rc->side_dist_y = (data_rc->y_map + 1.0 - data_rc->ypos_ray)
			* data_rc->delta_dist_y;
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
		data_rc->pwall_dist = fabs(((double)data_rc->x_map - data_rc->xpos_ray
					+ (1 - (double)data_rc->x_step) * 0.5) / data_rc->xdir_ray);
	else
		data_rc->pwall_dist = fabs(((double)data_rc->y_map - data_rc->ypos_ray
					+ (1 - (double)data_rc->y_step) * 0.5) / data_rc->ydir_ray);
}

void	raycasting(t_data *data, struct s_raycast *data_rc)
{
	int	x;

	x = 0;
	data->zbuffer = malloc((data->screen_res[0] + 1) * sizeof(double));
	ft_bzero(data->zbuffer, data->screen_res[0] + 1);
	data_rc->height = data->screen_res[1];
	data_rc->width = data->screen_res[0];
	while (x < data_rc->width)
	{
		get_value(data, data_rc, x);
		get_initial_dist(data_rc);
		get_wall(data, data_rc);
		print_column(data, data_rc, x);
		data->zbuffer[x] = data_rc->pwall_dist;
		x++;
	}
	if (data->ennemy.pres)
		print_sprite(data, data_rc);
	if (data->zbuffer)
	{
		free(data->zbuffer);
		data->zbuffer = NULL;
	}
}
