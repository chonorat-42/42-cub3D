/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_column.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:35:56 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/14 13:43:57 by pgouasmi         ###   ########.fr       */
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

static int	get_color_sprite(t_data *data, int x, int y)
{
	int		color;
	int		index;

	data->ghost.addr = mlx_get_data_addr(data->ghost.img, &data->ghost.bpp, &data->ghost.line_length, &data->ghost.endian);
	index = (y * data->ghost.line_length) + (x * (data->ghost.bpp / 8));
	color = (*(unsigned int *)(data->ghost.addr + index));
	return (color);
}

void	print_sprite(t_data *data, struct s_raycast *data_rc)
{
	int	start_y;
	int	end_y;
	int	start_x;
	int	end_x;
	int	index;
	int	tex_x;
	int	tex_y;
	int	color;
	int	d;
	int	y;

	data_rc->ennemy.distance = (data->player.x_pos - data->ennemy.d_pos[1]) * (data->player.x_pos - data->ennemy.d_pos[1])
							+ (data->player.y_pos - data->ennemy.d_pos[0]) * (data->player.y_pos - data->ennemy.d_pos[0]);
	data_rc->ennemy.sprite_x = data->ennemy.d_pos[1] - data->player.x_pos;
	data_rc->ennemy.sprite_y = data->ennemy.d_pos[0] - data->player.y_pos;
	data_rc->ennemy.inv_det = 1.0 / (data->player.x_plane * data->player.y_dir - data->player.y_plane * data->player.x_dir);
	data_rc->ennemy.x_transform = data_rc->ennemy.inv_det * (data->player.y_dir * data_rc->ennemy.sprite_x - data->player.x_dir * data_rc->ennemy.sprite_y);
	data_rc->ennemy.y_transform = data_rc->ennemy.inv_det * (-data->player.y_plane * data_rc->ennemy.sprite_x + data->player.x_plane * data_rc->ennemy.sprite_y);
	data_rc->ennemy.screen_x = (int)(data_rc->width * 0.5) * (1 + data_rc->ennemy.x_transform / data_rc->ennemy.y_transform);
	data_rc->ennemy.sprite_h = abs((int)(data_rc->height / data_rc->ennemy.y_transform));
	start_y = -data_rc->ennemy.sprite_h * 0.5 + data_rc->height * 0.5;
	if (start_y < 0)
		start_y = 0;
	end_y = data_rc->ennemy.sprite_h * 0.5 + data_rc->height * 0.5;
	if (end_y >= data_rc->height)
		end_y = data_rc->height;
	data_rc->ennemy.sprite_w = abs((int)(data_rc->height / data_rc->ennemy.y_transform));
	start_x = -data_rc->ennemy.sprite_w * 0.5 + data_rc->ennemy.screen_x;
	if (start_x < 0)
		start_x = 0;
	end_x = data_rc->ennemy.sprite_w * 0.5 + data_rc->ennemy.screen_x;
	if (end_x >= data_rc->width)
		end_x = data_rc->width;
	index = start_x;
	while (index < end_x)
	{
		tex_x = (int)(256 * (index - (-data_rc->ennemy.sprite_w / 2 + data_rc->ennemy.screen_x)) * 256 / data_rc->ennemy.sprite_w) / 256;
		if (data_rc->ennemy.y_transform > 0 && index >= 0 && index < data_rc->width && data_rc->ennemy.y_transform < data->zbuffer[index])
		{
			y = start_y;
			while (y < end_y)
			{
				d = (y) * 256 - data_rc->height * 128 + data_rc->ennemy.sprite_h * 128;
				tex_y = ((d * 256) / data_rc->ennemy.sprite_h) / 256;
				color = get_color_sprite(data, tex_x, tex_y);
				if (color != (int)0x0)
				{
					color = get_fog(color, data->fog_density, data->zbuffer[index]);
					pixel_to_frame(data, index, y, color);
				}
				y++;
			}
		}
		index++;
	}
}

void	print_column(t_data *data, struct s_raycast *data_rc, int x)
{
	int	y;

	data_rc->print.h_line = fabs((data_rc->height / data_rc->pwall_dist));
	data_rc->print.start = (-data_rc->print.h_line / 2)
		+ (data_rc->height / 2);
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
		data_rc->print.color = get_fog((int)data->colors.floor, data->fog_density, data_rc->pwall_dist);
		pixel_to_frame(data, x, y, data_rc->print.color);
		data_rc->print.color = get_fog((int)data->colors.ceiling, data->fog_density, data_rc->pwall_dist);
		pixel_to_frame(data, x, data_rc->height - y++ - 1,
			data_rc->print.color);
	}
}
