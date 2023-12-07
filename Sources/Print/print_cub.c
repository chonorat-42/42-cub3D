/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/07 13:17:46 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_ennemy(t_data *data)
{
	if ((int)data->ennemy.path->coor[0] == (int)data->ennemy.d_pos[0]
		&& (int)data->ennemy.path->coor[1] == (int)data->ennemy.d_pos[1])
	{
		if (data->ennemy.path->next)
			data->ennemy.path = data->ennemy.path->next;
	}
	if (data->ennemy.d_pos[0] < data->ennemy.path->coor[0])
		data->ennemy.d_pos[0] += ENNEMY_SPEED;
	if (data->ennemy.d_pos[0] > data->ennemy.path->coor[0])
		data->ennemy.d_pos[0] -= ENNEMY_SPEED;
	if (data->ennemy.d_pos[1] < data->ennemy.path->coor[1])
		data->ennemy.d_pos[1] += ENNEMY_SPEED;
	if (data->ennemy.d_pos[1] > data->ennemy.path->coor[1])
		data->ennemy.d_pos[1] -= ENNEMY_SPEED;
}

int	print_cub(t_data *data)
{
	struct s_raycast	data_rc;

	//if (data->)
	if ((int)data->ennemy.target[0] != (int)data->player.y_pos
		|| (int)data->ennemy.target[1] != (int)data->player.x_pos)
	{
		solve_maze(data, data->map, (int)data->player.y_pos, (int)data->player.x_pos);
	}
	move_ennemy(data);
	init_raycast(&data_rc);
	get_move(data);
	raycasting(data, &data_rc);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	print_minimap(data);
	return (1);
}
