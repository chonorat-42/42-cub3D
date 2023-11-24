/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:10:11 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/24 18:42:39 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	
	data->player.x_pos = 20.5 * (data->screen_res[1] >> 7);
	data->player.y_pos = 5.3 * (data->screen_res[1] >> 7);
	print_cub(data);
	mlx_loop_hook(data->mlx.mlx, print_cub, data);
	mlx_hook(data->mlx.window, ON_DESTROY, 0L, exit_prog, data);
	mlx_loop(data->mlx.mlx);
	return (1);
}
