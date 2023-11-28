/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:10:11 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/28 17:36:46 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	key_press(int keycode, t_data *data)
{
	if (keycode == MAJ)
		data->player.move.sprint = 1;
	if (keycode == L_MOVE)
		data->player.move.l_move = 1;
	if (keycode == R_MOVE)
		data->player.move.r_move = 1;
	if (keycode == F_MOVE)
		data->player.move.f_move = 1;
	if (keycode == B_MOVE)
		data->player.move.b_move = 1;
	if (keycode == ESC)
		exit_prog(data);
	return (1);
}

static int	key_release(int keycode, t_data *data)
{
	if (keycode == MAJ)
		data->player.move.sprint = 0;
	if (keycode == L_MOVE)
		data->player.move.l_move = 0;
	if (keycode == R_MOVE)
		data->player.move.r_move = 0;
	if (keycode == F_MOVE)
		data->player.move.f_move = 0;
	if (keycode == B_MOVE)
		data->player.move.b_move = 0;
	return (1);
}

static void	init_plane(t_data *data)
{
	double	length;

	data->player.x_plane = data->player.y_dir;
	data->player.y_plane = -data->player.x_dir;
	length = sqrt(pow(data->player.x_plane, 2) + pow(data->player.y_plane, 2));
	data->player.x_plane /= length;
	data->player.y_plane /= length;
}

static int	get_ratio(t_data *data, int minimap_x, int minimap_y)
{
	int	ratio_x;
	int	ratio_y;

	ratio_x = data->screen_res[0] / minimap_x;
	ratio_y = data->screen_res[1] / minimap_y;
	return ((ratio_x + ratio_y) / 2);
}

int	start_mlx(t_data *data)
{
	mlx_get_screen_size(data->mlx.mlx, &data->screen_res[0],
		&data->screen_res[1]);
	//data->screen_res[0] = 1920;
	//data->screen_res[1] = 1080;
	data->mlx.window = mlx_new_window(data->mlx.mlx, data->screen_res[0],
			data->screen_res[1], "cub3D");
	if (!data->mlx.window)
		return (0);
	data->minimap_ratio = get_ratio(data, ft_strlen(data->map[0]), ft_arr_size(data->map)) / 8; 
	init_plane(data);
	mlx_loop_hook(data->mlx.mlx, print_cub, data);
	mlx_hook(data->mlx.window, KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->mlx.window, KEY_RELEASE, 1L << 1, key_release, data);
	mlx_hook(data->mlx.window, ON_DESTROY, 0L, exit_prog, data);
	mlx_loop(data->mlx.mlx);
	return (1);
}
