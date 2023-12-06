/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_column.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:56 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/06 18:20:24 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	index = (y * data_rc->wall.line_length) + (x * (data_rc->wall.bpp * 0.125));
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
		tex_y = (int)(((y - (data->screen_res[1] >> 1)
						+ (data_rc->print.h_line >> 1)) * 256)
				/ data_rc->print.h_line);
		color = get_pixel_color(data_rc, tex_x, tex_y);
		color = get_fog(data_rc, color, 1.8);
		pixel_to_frame(data, x, y, color);
		y++;
	}
}

void	print_column(t_data *data, struct s_raycast *data_rc, int x)
{
	int	y;

	data_rc->print.h_line = fabs((data_rc->height / data_rc->pwall_dist));
	data_rc->print.start = (-data_rc->print.h_line >> 1)
		+ (data_rc->height >> 1);
	data_rc->print.end = (data_rc->print.h_line >> 1) + (data_rc->height >> 1);
	if (data_rc->print.start < 0)
		data_rc->print.start = 0;
	if (data_rc->print.end >= data_rc->height)
		data_rc->print.end = data_rc->height - 1;
	y = data_rc->print.start;
	if (data_rc->print.end < 0)
		data_rc->print.end = data_rc->height;
	print_texture(data, data_rc, x, y);
	y = data_rc->print.end;
	while (y < data_rc->height)
	{
		data_rc->print.color = get_fog(data_rc, (int)0x1a1a1a, 1.8);
		pixel_to_frame(data, x, y, data_rc->print.color);
		data_rc->print.color = get_fog(data_rc, (int)0x0, 1.8);
		pixel_to_frame(data, x, data_rc->height - y++ - 1,
			data_rc->print.color);
	}
}
