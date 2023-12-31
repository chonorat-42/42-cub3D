/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:10:11 by chonorat          #+#    #+#             */
/*   Updated: 2024/01/04 12:58:00 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_ratio(t_data *data, int minimap_x, int minimap_y)
{
	int	ratio_x;
	int	ratio_y;

	ratio_x = data->screen_res[0] / minimap_x;
	ratio_y = data->screen_res[1] / minimap_y;
	return ((ratio_x + ratio_y) / 2);
}

static void	get_screen_res(t_data *data)
{
	data->screen_res[0] = 1920;
	data->screen_res[1] = 1080;
}

int	start_mlx(t_data *data)
{
	get_screen_res(data);
	data->mlx.window = mlx_new_window(data->mlx.mlx, data->screen_res[0],
			data->screen_res[1], "cub3D");
	if (!data->mlx.window)
		return (0);
	data->mlx.frame.img = mlx_new_image(data->mlx.mlx, data->screen_res[0],
			data->screen_res[1]);
	data->mlx.frame.addr = mlx_get_data_addr(data->mlx.frame.img,
			&data->mlx.frame.bpp, &data->mlx.frame.line_length,
			&data->mlx.frame.endian);
	data->minimap_ratio = get_ratio(data, ft_strlen(data->map[0]),
			ft_arr_size(data->map)) / 8;
	initstart_ennemy(data);
	mlx_loop_hook(data->mlx.mlx, execution, data);
	mlx_mouse_hook(data->mlx.window, mouse_hook, data);
	mlx_hook(data->mlx.window, KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->mlx.window, KEY_RELEASE, 1L << 1, key_release, data);
	mlx_hook(data->mlx.window, ON_DESTROY, 0L, exit_prog, data);
	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.window, &data->mouse_pos[0],
		&data->mouse_pos[1]);
	mlx_mouse_hide(data->mlx.mlx, data->mlx.window);
	mlx_loop(data->mlx.mlx);
	return (1);
}
