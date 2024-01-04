/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:23:46 by chonorat          #+#    #+#             */
/*   Updated: 2024/01/04 13:02:35 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	mouse_on_pause(t_data *data)
{
	if (data->mouse_pos[0] >= 925 && data->mouse_pos[0] <= 1015
		&& data->mouse_pos[1] >= 460 && data->mouse_pos[1] <= 490)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) - 60,
			(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, ">");
		data->pause_menu.on_resume = 1;
	}
	else if (data->mouse_pos[0] >= 920 && data->mouse_pos[0] <= 1020
		&& data->mouse_pos[1] >= 520 && data->mouse_pos[1] <= 550)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) - 60,
			(data->screen_res[1] >> 1), (int)0xFFFFFF, ">");
		data->pause_menu.on_options = 1;
	}
	else if (data->mouse_pos[0] >= 940 && data->mouse_pos[0] <= 995
		&& data->mouse_pos[1] >= 570 && data->mouse_pos[1] <= 600)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) - 60,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, ">");
		data->pause_menu.on_exit = 1;
	}
}

static void	show_pause_text(t_data *data)
{
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	mouse_on_pause(data);
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 25,
		(data->screen_res[1] >> 1) - 300, (int)0xFFFFFF, "PAUSE");
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 27,
		(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "Resume");
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 33,
		(data->screen_res[1] >> 1), (int)0xFFFFFF, "Options");
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 17,
		(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "Quit");
}

void	pause_menu(t_data *data)
{
	init_pause(data);
	mlx_set_font(data->mlx.mlx, data->mlx.window, STD_FONT);
	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.window,
		&data->mouse_pos[0], &data->mouse_pos[1]);
	if (data->pause_menu.in_options)
		show_options_text(data);
	else
		show_pause_text(data);
}
