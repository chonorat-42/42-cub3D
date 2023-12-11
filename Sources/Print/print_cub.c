/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/08 22:07:15 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_ennemy(t_data *data)
{
	if (!data->ennemy.path)
	{
		printf("NO_PATH\n");
		return ;
	}
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
	data->ennemy.pos[0] = (int)data->ennemy.d_pos[0];
	data->ennemy.pos[1] = (int)data->ennemy.d_pos[1];
}

int	print_cub(t_data *data)
{
	struct s_raycast	data_rc;

	if ((int)data->ennemy.target[0] != (int)data->player.y_pos
		|| (int)data->ennemy.target[1] != (int)data->player.x_pos
		|| !data->ennemy.path)
	{
		solve_maze(data, data->map, (int)data->player.y_pos, (int)data->player.x_pos);
	}
	move_ennemy(data);
	init_raycast(&data_rc);
	get_move(data);
	raycasting(data, &data_rc);
	print_minimap(data);
	mlx_clear_window(data->mlx.mlx, data->mlx.window);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
	return (1);
}
