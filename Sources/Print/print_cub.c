/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/13 14:43:52 by chonorat         ###   ########lyon.fr   */
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
		data->ennemy.d_pos[0] += ENNEMY_SPEED;
	if (data->ennemy.d_pos[0] > data->ennemy.path->coor[0])
		data->ennemy.d_pos[0] -= ENNEMY_SPEED;
	if (data->ennemy.d_pos[1] < data->ennemy.path->coor[1])
		data->ennemy.d_pos[1] += ENNEMY_SPEED;
	if (data->ennemy.d_pos[1] > data->ennemy.path->coor[1])
		data->ennemy.d_pos[1] -= ENNEMY_SPEED;
	data->ennemy.pos[0] = (int)data->ennemy.d_pos[0];
	data->ennemy.pos[1] = (int)data->ennemy.d_pos[1];
	free_path(&data->ennemy.path);
}

static void	game_execution(t_data *data)
{
	free_path(&data->ennemy.path);
	if (data->parser.map[(int)data->player.y_pos][(int)data->player.x_pos] == 'V')
		return (printf("Win\n"), free_data(data), exit(0));
	if (data->ennemy.pres)
	{
		if (difference(data->ennemy.d_pos[0], data->player.y_pos) <= 0.05 && difference(data->ennemy.d_pos[1], data->player.x_pos) <= 0.05)
			return (printf("mort\n"), free_data(data), exit(0));
		if (data->ennemy.target[0] != data->player.y_pos
			|| data->ennemy.target[1] != data->player.x_pos
			|| !data->ennemy.path)
			pathfinding(data, data->map, (int)data->player.y_pos, (int)data->player.x_pos);
		move_ennemy(data);
	}
	get_move(data);
	raycasting(data);
	print_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
}

static void	mouse_on(t_data *data)
{
	//printf("mY[%d], mX[%d]\n", data->mouse_pos[0], data->mouse_pos[1]);
	if (data->pause_menu.in_options)
		printf("WIP\n");
	else
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
}

static void	show_pause_text(t_data *data)
{
	mlx_set_font(data->mlx.mlx, data->mlx.window, FONT);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	mouse_on(data);
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 25,
		(data->screen_res[1] >> 1) - 300, (int)0xFFFFFF, "PAUSE");
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 27,
		(data->screen_res[1] >> 1) - 55, (int)0xFFFFFF, "Resume");
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 33,
		(data->screen_res[1] >> 1), (int)0xFFFFFF, "Options");
	mlx_string_put(data->mlx.mlx, data->mlx.window, (data->screen_res[0] >> 1) - 17,
		(data->screen_res[1] >> 1) + 55, (int)0xFFFFFF, "Exit");
}

static void	pause_menu(t_data *data)
{
	init_pause(data);
	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.window,
			&data->mouse_pos[0], &data->mouse_pos[1]);
	show_pause_text(data);
}

int	execution(t_data *data)
{
	if (data->pause_menu.in_pause)
		pause_menu(data);
	else
		game_execution(data);
	return (1);
}
