/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:10:11 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/26 00:52:45 by chonorat         ###   ########.fr       */
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

static char	**getTempMap(void)
{
	char	**temp = NULL;
	int		index = 0;

	temp = malloc(sizeof(char *) * 11);
	temp[index++] = ft_strdup("1111111111111111111111111111111111111111");
	while (index < 8)
		temp[index++] = ft_strdup("1000000000000000000000000000000000000001");
	temp[index++] = ft_strdup("1000000010000000000N00000000000000000001");
	temp[index++] = ft_strdup("1111111111111111111111111111111111111111");
	temp[index] = NULL;
	return (temp);
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
	data->map = getTempMap();
	data->player.x_pos = 20.5;
	data->player.y_pos = 5.3;
	print_cub(data);
	mlx_loop_hook(data->mlx.mlx, print_cub, data);
	mlx_hook(data->mlx.window, KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->mlx.window, KEY_RELEASE, 1L << 1, key_release, data);
	mlx_hook(data->mlx.window, ON_DESTROY, 0L, exit_prog, data);
	mlx_loop(data->mlx.mlx);
	return (1);
}
