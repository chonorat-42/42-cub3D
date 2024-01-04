/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:28:02 by chonorat          #+#    #+#             */
/*   Updated: 2024/01/04 13:03:10 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	options_next(t_data *data)
{
	if (data->mouse_pos[0] >= 850 && data->mouse_pos[0] <= 1150
		&& data->mouse_pos[1] >= 470 && data->mouse_pos[1] <= 500)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) - 130,
			(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, ">");
		data->pause_menu.on_difficulty = 1;
	}
	else if (data->mouse_pos[0] >= 850 && data->mouse_pos[0] <= 1085
		&& data->mouse_pos[1] >= 405 && data->mouse_pos[1] <= 435)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) - 130,
			(data->screen_res[1] >> 1) - 110, (int)0xFFFFFF, ">");
		data->pause_menu.on_minimap = 1;
	}
	else if (data->mouse_pos[0] >= 850 && data->mouse_pos[0] <= 1115
		&& data->mouse_pos[1] >= 570 && data->mouse_pos[1] <= 600)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) - 130,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, ">");
		data->pause_menu.on_mouse_sens = 1;
	}
}

static void	mouse_on_options(t_data *data)
{
	if (data->mouse_pos[0] >= 940 && data->mouse_pos[0] <= 995
		&& data->mouse_pos[1] >= 620 && data->mouse_pos[1] <= 650)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) - 50,
			(data->screen_res[1] >> 1) + 110, (int)0xFFFFFF, ">");
		data->pause_menu.on_back = 1;
	}
	else if (data->mouse_pos[0] >= 850 && data->mouse_pos[0] <= 1150
		&& data->mouse_pos[1] >= 520 && data->mouse_pos[1] <= 550)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) - 130,
			(data->screen_res[1] >> 1), (int)0xFFFFFF, ">");
		data->pause_menu.on_fog = 1;
	}
	else
		options_next(data);
}

void	show_options_text(t_data *data)
{
	raycasting(data);
	if (data->minimap_toggle)
		print_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	mouse_on_options(data);
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 35,
		(data->screen_res[1] >> 1) - 300, (int)0xFFFFFF, "OPTIONS");
	show_fog(data);
	show_difficulty(data);
	show_minimap(data);
	show_mouse_sens(data);
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 17,
		(data->screen_res[1] >> 1) + 110, (int)0xFFFFFF, "Back");
}
