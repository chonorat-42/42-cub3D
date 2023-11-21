/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:10:11 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/21 15:05:16 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	start_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (0);
	mlx_get_screen_size(data->mlx.mlx, &data->screen_res[0],
		&data->screen_res[1]);
	data->mlx.window = mlx_new_window(data->mlx.mlx, data->screen_res[0],
		data->screen_res[1], "cub3D");
	if (!data->mlx.window)
		return (0);
	mlx_hook(data->mlx.window, ON_DESTROY, 0L, exit_prog, data);
	mlx_loop(data->mlx.mlx);
	return (1);
}