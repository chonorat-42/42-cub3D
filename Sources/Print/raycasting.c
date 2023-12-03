/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:10:01 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/02 20:10:01 by chonorat         ###   ########.fr       */
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
		data_rc->pwall_dist = fabs(((double)data_rc->x_map - data_rc->xpos_ray
			+ (1 - (double)data_rc->x_step) / 2) / data_rc->xdir_ray);
	else
		data_rc->pwall_dist = fabs(((double)data_rc->y_map - data_rc->ypos_ray
			+ (1 - (double)data_rc->y_step) / 2) / data_rc->ydir_ray);
}

static int	apply_fog(int color, double fog_factor)
{
	int	red;
	int	green;
	int	blue;

	red = (color >> 16) & 0xFF;
	red = (int)(red * fog_factor);
	green = (color >> 8) & 0xFF;
	green = (int)(green * fog_factor);
	blue = color & 0xFF;
	blue = (int)(blue * fog_factor);
	return ((red << 16) | (green << 8) | blue);
}

static int	get_fog(struct s_raycast *data_rc, int color, double fog_intensity)
{
	double	fog_factor;
	int		final_color;

	fog_factor = 1.0 / (data_rc->pwall_dist * fog_intensity);
	if (fog_factor > 0.5)
		fog_factor = 0.5;
	final_color = apply_fog(color, fog_factor);
	return (final_color);
}

static void	get_wall_side(t_data *data, struct s_raycast *data_rc)
{
	if (data_rc->wall_side == 0 && data_rc->xdir_ray > 0)
		data_rc->wall.img = data->tex_img.ea_img;
	else if (data_rc->wall_side == 0 && data_rc->xdir_ray < 0)
		data_rc->wall.img = data->tex_img.we_img;
	else if (data_rc->wall_side == 1 && data_rc->ydir_ray > 0)
		data_rc->wall.img = data->tex_img.so_img;
	else if (data_rc->wall_side == 1 && data_rc->ydir_ray < 0)
		data_rc->wall.img = data->tex_img.no_img;
}

static void get_wall_hit_point(struct s_raycast *data_rc)
{
	if (data_rc->wall_side == 0)
		data_rc->wall_hit_point = data_rc->ypos_ray + data_rc->pwall_dist * data_rc->ydir_ray;
	else
		data_rc->wall_hit_point = data_rc->xpos_ray + data_rc->pwall_dist * data_rc->xdir_ray;
	data_rc->wall_hit_point -= floor(data_rc->wall_hit_point);
}

static int get_pixel_color(struct s_raycast *data_rc, int x, int y)
{
	char *dst;
	int color;
	int index;

	dst = mlx_get_data_addr(data_rc->wall.img, &data_rc->wall.bpp, &data_rc->wall.line_length, &data_rc->wall.endian);
	index = (y * data_rc->wall.line_length) + (x * (data_rc->wall.bpp / 8));
	color = (*(unsigned int *)(dst + index));
	return (color);
}

static void	print_texture(t_data *data, struct s_raycast *data_rc, int x, int y, int end, int h_line)
{
	int	tex_x;
	int	tex_y;
	int color;

	get_wall_side(data, data_rc);
	get_wall_hit_point(data_rc);
	while (y < end)
	{
		tex_x = (int)(data_rc->wall_hit_point * 256);
		tex_y = (int)(((y - data->screen_res[1] / 2 + h_line / 2) * 256) / h_line);
		color = get_pixel_color(data_rc, tex_x, tex_y);
		color = get_fog(data_rc, color, 1.8);
		pixel_to_frame(data, x, y, color);
		y++;
	}
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
	if (end < 0)
		end = data_rc->height;
	print_texture(data, data_rc, x, y, end, h_line);
	y = end;
	while (y < data_rc->height)
	{
		color = get_fog(data_rc, (int)0x1a1a1a, 1.8);
		pixel_to_frame(data, x, y, color);
		color = get_fog(data_rc, (int)0x0, 1.8);
		pixel_to_frame(data, x, data_rc->height - y++ - 1, color);
	}
}

void	raycasting(t_data *data, struct s_raycast *data_rc)
{
	int	x;

	x = 0;
	data_rc->height = data->screen_res[1];
	data_rc->width = data->screen_res[0];
	while (x < data_rc->width)
	{
		get_value(data, data_rc, x);
		get_initial_dist(data_rc);
		get_wall(data, data_rc);
		print_column(data, data_rc, x);
		x++;
	}
}
