/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:34:47 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/17 16:06:09 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	print_background(t_data *data)
{
	int	index[2];

	index[0] = 0;
	while (index[0] < data->screen_res[0])
	{
		index[1] = 0;
		while (index[1] < data->screen_res[1])
			pixel_to_frame(data, index[0], index[1]++, (int)0x0);
		index[0]++;
	}
}

static void	mouse_on_death(t_data *data)
{
	if (data->mouse_pos[0] >= 870 && data->mouse_pos[0] <= 930
		&& data->mouse_pos[1] >= 570 && data->mouse_pos[1] <= 595)
	{
		data->pause_menu.on_exit = 0;
		data->pause_menu.on_retry = 1;
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) - 120,
			(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, ">");
	}
	else if (data->mouse_pos[0] >= 980 && data->mouse_pos[0] <= 1090
		&& data->mouse_pos[1] >= 570 && data->mouse_pos[1] <= 595)
	{
		data->pause_menu.on_retry = 0;
		data->pause_menu.on_exit = 1;
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 145,
			(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, "<");
	}
}

static void	mouse_on_escape(t_data *data)
{
	if (data->mouse_pos[0] >= 870 && data->mouse_pos[0] <= 955
		&& data->mouse_pos[1] >= 570 && data->mouse_pos[1] <= 595)
	{
		data->pause_menu.on_exit = 0;
		data->pause_menu.on_retry = 1;
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) - 120,
			(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, ">");
	}
	else if (data->mouse_pos[0] >= 980 && data->mouse_pos[0] <= 1090
		&& data->mouse_pos[1] >= 570 && data->mouse_pos[1] <= 595)
	{
		data->pause_menu.on_retry = 0;
		data->pause_menu.on_exit = 1;
		mlx_string_put(data->mlx.mlx, data->mlx.window,
			(data->screen_res[0] >> 1) + 145,
			(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, "<");
	}
}

void	escape_screen(t_data *data)
{
	init_pause(data);
	print_background(data);
	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.window,
		&data->mouse_pos[0], &data->mouse_pos[1]);
	mlx_mouse_show(data->mlx.mlx, data->mlx.window);
	mlx_set_font(data->mlx.mlx, data->mlx.window, HEAD_FONT);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 175,
		(data->screen_res[1] >> 1) - 50, (int)0xff00, "YOU ESCAPED");
	mlx_set_font(data->mlx.mlx, data->mlx.window, STD_FONT);
	mouse_on_escape(data);
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 90,
		(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, "Restart");
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) + 20,
		(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, "Quit game");
}

void	death_screen(t_data *data)
{
	print_background(data);
	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.window,
		&data->mouse_pos[0], &data->mouse_pos[1]);
	mlx_mouse_show(data->mlx.mlx, data->mlx.window);
	mlx_set_font(data->mlx.mlx, data->mlx.window, HEAD_FONT);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 200,
		(data->screen_res[1] >> 1) - 50, (int)0x8b0000, "YOU ARE DEAD");
	mlx_set_font(data->mlx.mlx, data->mlx.window, STD_FONT);
	mouse_on_death(data);
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) - 90,
		(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, "Retry");
	mlx_string_put(data->mlx.mlx, data->mlx.window,
		(data->screen_res[0] >> 1) + 20,
		(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, "Quit game");
}
