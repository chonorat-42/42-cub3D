/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:54:25 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/01 10:49:04 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	exit_prog(t_data *data)
{
	(void)data;
	mlx_destroy_window(data->mlx.mlx, data->mlx.window);
	free_data(data);
	exit(EXIT_SUCCESS);
}
