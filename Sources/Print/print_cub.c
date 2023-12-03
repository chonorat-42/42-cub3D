/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/03 16:42:26 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	print_cub(t_data *data)
{
	struct s_raycast	data_rc;

	init_raycast(&data_rc);
	get_move(data);
	raycasting(data, &data_rc);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	print_minimap(data);
	return (1);
}
