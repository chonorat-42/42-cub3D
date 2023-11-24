/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:10:11 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/24 16:35:30 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	start_mlx(t_data *data)
{
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
