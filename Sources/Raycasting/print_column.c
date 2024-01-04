/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_column.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:56 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/14 18:01:36 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_wall_side(t_data *data, struct s_raycast *data_rc)
{
	if (!data_rc->wall_side && data_rc->xdir_ray > 0 && data_rc->wall_hit == 1)
		data_rc->wall.img = data->tex_img.ea_img;
	else if (!data_rc->wall_side && data_rc->xdir_ray > 0
		&& data_rc->wall_hit == 2)
		data_rc->wall.img = data->tex_img.ea_exit_img;
	else if (!data_rc->wall_side && data_rc->xdir_ray < 0
		&& data_rc->wall_hit == 1)
		data_rc->wall.img = data->tex_img.we_img;
	else if (!data_rc->wall_side && data_rc->xdir_ray < 0
		&& data_rc->wall_hit == 2)
		data_rc->wall.img = data->tex_img.we_exit_img;
	else if (data_rc->wall_side == 1 && data_rc->ydir_ray > 0
		&& data_rc->wall_hit == 1)
		data_rc->wall.img = data->tex_img.so_img;
	else if (data_rc->wall_side == 1 && data_rc->ydir_ray > 0
		&& data_rc->wall_hit == 2)
		data_rc->wall.img = data->tex_img.so_exit_img;
	else if (data_rc->wall_side == 1 && data_rc->ydir_ray < 0
		&& data_rc->wall_hit == 1)
		data_rc->wall.img = data->tex_img.no_img;
	else if (data_rc->wall_side == 1 && data_rc->ydir_ray < 0
		&& data_rc->wall_hit == 2)
		data_rc->wall.img = data->tex_img.no_exit_img;
}

static void	get_wall_hit_point(struct s_raycast *data_rc)
{
	if (data_rc->wall_side == 0)
		data_rc->wall_hit_point = data_rc->ypos_ray + data_rc->pwall_dist
			* data_rc->ydir_ray;
	else
		data_rc->wall_hit_point = data_rc->xpos_ray + data_rc->pwall_dist
			* data_rc->xdir_ray;
	data_rc->wall_hit_point -= floor(data_rc->wall_hit_point);
}

static int	get_pixel_color(struct s_raycast *data_rc, int x, int y)
{
	char	*dst;
	int		color;
	int		index;

	dst = mlx_get_data_addr(data_rc->wall.img, &data_rc->wall.bpp,
			&data_rc->wall.line_length, &data_rc->wall.endian);
	index = (y * data_rc->wall.line_length) + (x * (data_rc->wall.bpp / 8));
	color = (*(unsigned int *)(dst + index));
	return (color);
}

static void	print_texture(t_data *data, struct s_raycast *data_rc, int x, int y)
{
	int	tex_x;
	int	tex_y;
	int	color;

	get_wall_side(data, data_rc);
	get_wall_hit_point(data_rc);
	while (y < data_rc->print.end)
	{
		tex_x = (int)(data_rc->wall_hit_point * 256);
		tex_y = (int)(((y - (data->screen_res[1] / 2)
						+ (data_rc->print.h_line / 2)) * 256)
				/ data_rc->print.h_line);
		color = get_pixel_color(data_rc, tex_x, tex_y);
		color = get_fog(color, data->fog_density, data_rc->pwall_dist);
		pixel_to_frame(data, x, y, color);
		y++;
	}
}

void	print_column(t_data *data, struct s_raycast *data_rc, int x)
{
	int	y;

	data_rc->print.h_line = fabs((data_rc->height / data_rc->pwall_dist));
	data_rc->print.start = (-data_rc->print.h_line / 2 + (data_rc->height / 2));
	data_rc->print.end = data->screen_res[1] - data_rc->print.start;
	if (data_rc->print.start < 0)
		data_rc->print.start = 0;
	if (data_rc->print.end >= data_rc->height)
		data_rc->print.end = data_rc->height - 1;
	y = data_rc->print.start;
	if (data_rc->print.end < 0)
		data_rc->print.end = data_rc->height;
	if (y < data_rc->print.end)
		print_texture(data, data_rc, x, y);
	y = data_rc->print.end;
	while (y < data_rc->height)
	{
		data_rc->print.color = get_fog((int)data->colors.floor,
				data->fog_density, data_rc->pwall_dist);
		pixel_to_frame(data, x, y, data_rc->print.color);
		data_rc->print.color = get_fog((int)data->colors.ceiling,
				data->fog_density, data_rc->pwall_dist);
		pixel_to_frame(data, x, data_rc->height - y++ - 1,
			data_rc->print.color);
	}
}
