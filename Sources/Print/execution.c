/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/14 14:25:40 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_ennemy(t_data *data)
{
	if (!data->ennemy.path)
		return ;
	if ((int)data->ennemy.path->coor[0] == (int)data->ennemy.d_pos[0]
		&& (int)data->ennemy.path->coor[1] == (int)data->ennemy.d_pos[1])
	{
		if (data->ennemy.path->next)
			data->ennemy.path = data->ennemy.path->next;
		else if ((int)data->ennemy.path->coor[0] == (int)data->player.y_pos
			&& (int)data->ennemy.path->coor[1] == (int)data->player.x_pos)
		{
			data->ennemy.path->coor[0] = data->player.y_pos;
			data->ennemy.path->coor[1] = data->player.x_pos;
		}
	}
	if (data->ennemy.d_pos[0] < data->ennemy.path->coor[0])
		data->ennemy.d_pos[0] += data->ennemy.speed;
	if (data->ennemy.d_pos[0] > data->ennemy.path->coor[0])
		data->ennemy.d_pos[0] -= data->ennemy.speed;
	if (data->ennemy.d_pos[1] < data->ennemy.path->coor[1])
		data->ennemy.d_pos[1] += data->ennemy.speed;
	if (data->ennemy.d_pos[1] > data->ennemy.path->coor[1])
		data->ennemy.d_pos[1] -= data->ennemy.speed;
	data->ennemy.pos[0] = (int)data->ennemy.d_pos[0];
	data->ennemy.pos[1] = (int)data->ennemy.d_pos[1];
	free_path(&data->ennemy.path);
}

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
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 120,
			(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, ">");
	}
	else if (data->mouse_pos[0] >= 980 && data->mouse_pos[0] <= 1090
		&& data->mouse_pos[1] >= 570 && data->mouse_pos[1] <= 595)
	{
		data->pause_menu.on_retry = 0;
		data->pause_menu.on_exit = 1;
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 145,
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
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 120,
			(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, ">");
	}
	else if (data->mouse_pos[0] >= 980 && data->mouse_pos[0] <= 1090
		&& data->mouse_pos[1] >= 570 && data->mouse_pos[1] <= 595)
	{
		data->pause_menu.on_retry = 0;
		data->pause_menu.on_exit = 1;
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 145,
			(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, "<");
	}
}

static void	escape_screen(t_data *data)
{
	init_pause(data);
	print_background(data);
	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.window,
			&data->mouse_pos[0], &data->mouse_pos[1]);
	printf("mY[%d], mX[%d]\n", data->mouse_pos[0], data->mouse_pos[1]);
	mlx_mouse_show(data->mlx.mlx, data->mlx.window);
	mlx_set_font(data->mlx.mlx, data->mlx.window, HEAD_FONT);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 175,
			(data->screen_res[1] >> 1) - 50, (int)0xff00, "YOU ESCAPED");
	mlx_set_font(data->mlx.mlx, data->mlx.window, STD_FONT);
	mouse_on_escape(data);
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 90,
			(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, "Restart");
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 20,
			(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, "Quit game");
}

static void	death_screen(t_data *data)
{
	print_background(data);
	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.window,
			&data->mouse_pos[0], &data->mouse_pos[1]);
	printf("mY[%d], mX[%d]\n", data->mouse_pos[0], data->mouse_pos[1]);
	mlx_mouse_show(data->mlx.mlx, data->mlx.window);
	mlx_set_font(data->mlx.mlx, data->mlx.window, HEAD_FONT);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 200,
			(data->screen_res[1] >> 1) - 50, (int)0x8b0000, "YOU ARE DEAD");
	mlx_set_font(data->mlx.mlx, data->mlx.window, STD_FONT);
	mouse_on_death(data);
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 90,
			(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, "Retry");
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 20,
			(data->screen_res[1] >> 1) + 50, (int)0xFFFFFF, "Quit game");
}

static void	game_execution(t_data *data)
{
	free_path(&data->ennemy.path);
	if (data->parser.map[(int)data->player.y_pos][(int)data->player.x_pos] == 'V')
		return (data->pause_menu.in_escape = 1, escape_screen(data));
	if (data->ennemy.pres)
	{
		if (difference(data->ennemy.d_pos[0], data->player.y_pos) <= 0.05 && difference(data->ennemy.d_pos[1], data->player.x_pos) <= 0.05)
			return (data->pause_menu.in_death = 1, death_screen(data));
		if (data->ennemy.target[0] != data->player.y_pos
			|| data->ennemy.target[1] != data->player.x_pos
			|| !data->ennemy.path)
			pathfinding(data, data->map, (int)data->player.y_pos, (int)data->player.x_pos);
		move_ennemy(data);
	}
	get_move(data);
	raycasting(data);
	if (data->minimap_toggle)
		print_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
}

static void	mouse_on_pause(t_data *data)
{
	if (data->mouse_pos[0] >= 925 && data->mouse_pos[0] <= 1015
		&& data->mouse_pos[1] >= 460 && data->mouse_pos[1] <= 490)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 60,
			(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, ">");
		data->pause_menu.on_resume = 1;
	}
	else if (data->mouse_pos[0] >= 920 && data->mouse_pos[0] <= 1020
		&& data->mouse_pos[1] >= 520 && data->mouse_pos[1] <= 550)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 60,
			(data->screen_res[1] >> 1), (int)0xFFFFFF, ">");
		data->pause_menu.on_options = 1;
	}
	else if (data->mouse_pos[0] >= 940 && data->mouse_pos[0] <= 995
		&& data->mouse_pos[1] >= 570 && data->mouse_pos[1] <= 600)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 60,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, ">");
			data->pause_menu.on_exit = 1;
	}
}


static void	mouse_on_options(t_data *data)
{
	printf("mY[%d], mX[%d]\n", data->mouse_pos[0], data->mouse_pos[1]);
	if (data->mouse_pos[0] >= 940 && data->mouse_pos[0] <= 995
		&& data->mouse_pos[1] >= 620 && data->mouse_pos[1] <= 650)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 50,
			(data->screen_res[1] >> 1) + 110, (int)0xFFFFFF, ">");
			data->pause_menu.on_back = 1;
	}
	else if (data->mouse_pos[0] >= 850 && data->mouse_pos[0] <= 1150
		&& data->mouse_pos[1] >= 520 && data->mouse_pos[1] <= 550)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 130,
			(data->screen_res[1] >> 1), (int)0xFFFFFF, ">");
			data->pause_menu.on_fog = 1;
	}
	else if (data->mouse_pos[0] >= 850 && data->mouse_pos[0] <= 1150
		&& data->mouse_pos[1] >= 470 && data->mouse_pos[1] <= 500)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 130,
			(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, ">");
			data->pause_menu.on_difficulty = 1;
	}
	else if (data->mouse_pos[0] >= 850 && data->mouse_pos[0] <= 1085
		&& data->mouse_pos[1] >= 405 && data->mouse_pos[1] <= 435)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 130,
			(data->screen_res[1] >> 1) - 110, (int)0xFFFFFF, ">");
			data->pause_menu.on_minimap = 1;
	}
	else if (data->mouse_pos[0] >= 850 && data->mouse_pos[0] <= 1115
		&& data->mouse_pos[1] >= 570 && data->mouse_pos[1] <= 600)
	{
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 130,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, ">");
			data->pause_menu.on_mouse_sens = 1;
	}
}

static void	show_difficulty(t_data *data)
{
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 100,
		(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "Difficulty :");
	if (data->difficulty == EASY)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 60,
		(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "EASY");
	else if (data->difficulty == NORMAL)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 60,
		(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "NORMAL");
	else if (data->difficulty == HARD)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 60,
		(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "HARD");
	else if (data->difficulty == IMPOSSIBLE)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 60,
		(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "IMPOSSIBLE");
}

static void	show_pause_text(t_data *data)
{
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	mouse_on_pause(data);
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 25,
		(data->screen_res[1] >> 1) - 300, (int)0xFFFFFF, "PAUSE");
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 27,
		(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "Resume");
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 33,
		(data->screen_res[1] >> 1), (int)0xFFFFFF, "Options");
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 17,
		(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "Exit");
}

static void	show_fog(t_data *data)
{
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 100,
		(data->screen_res[1] >> 1), (int)0xFFFFFF, "Fog density :");
	if (data->fog_setting == LOW)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 70,
		(data->screen_res[1] >> 1), (int)0xFFFFFF, "LOW");
	else if (data->fog_setting == MEDIUM)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 70,
		(data->screen_res[1] >> 1), (int)0xFFFFFF, "MEDIUM");
	else if (data->fog_setting == HIGH)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 70,
		(data->screen_res[1] >> 1), (int)0xFFFFFF, "HIGH");
	else if (data->fog_setting == VERY_HIGH)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 70,
		(data->screen_res[1] >> 1), (int)0xFFFFFF, "VERY HIGH");
}

static void	show_minimap(t_data *data)
{
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 100,
		(data->screen_res[1] >> 1) - 110, (int)0xFFFFFF, "Minimap :");
	if (data->minimap_toggle)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 20,
		(data->screen_res[1] >> 1) - 110, (int)0xFFFFFF, "ENABLED");
	else if (!data->minimap_toggle)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 20,
		(data->screen_res[1] >> 1) - 110, (int)0xFFFFFF, "DISABLED");
}

static void	show_mouse_sens(t_data *data)
{
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 100,
		(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "Mouse sensibility :");
	if (data->mouse_settings == 1)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 140,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "1");
	else if (data->mouse_settings == 2)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 140,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "2");
	else if (data->mouse_settings == 3)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 140,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "3");
	else if (data->mouse_settings == 4)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 140,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "4");
	else if (data->mouse_settings == 5)
		mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) + 140,
			(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "5");
}

static void	show_options_text(t_data *data)
{
	raycasting(data);
	if (data->minimap_toggle)
		print_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	mouse_on_options(data);
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 35,
		(data->screen_res[1] >> 1) - 300, (int)0xFFFFFF, "OPTIONS");
	show_fog(data);
	show_difficulty(data);
	show_minimap(data);
	show_mouse_sens(data);
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 17,
		(data->screen_res[1] >> 1) + 110, (int)0xFFFFFF, "Back");
}

static void	pause_menu(t_data *data)
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

int	execution(t_data *data)
{
	if (data->pause_menu.in_pause && !data->pause_menu.in_death
		&& !data->pause_menu.in_escape)
		pause_menu(data);
	else if (data->pause_menu.in_death)
		death_screen(data);
	else if (data->pause_menu.in_escape)
		escape_screen(data);
	else
		game_execution(data);
	return (1);
}
