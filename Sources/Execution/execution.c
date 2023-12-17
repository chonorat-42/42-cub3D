/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/17 15:38:47 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	game_execution(t_data *data)
{
	free_path(&data->ennemy.path);
	if (data->parser.map[(int)data->player.y_pos]
		[(int)data->player.x_pos] == 'V')
		return (data->pause_menu.in_escape = 1, escape_screen(data));
	if (data->ennemy.pres)
	{
		if (difference(data->ennemy.d_pos[0], data->player.y_pos) <= 0.05
			&& difference(data->ennemy.d_pos[1], data->player.x_pos) <= 0.05)
			return (data->pause_menu.in_death = 1, death_screen(data));
		if (data->ennemy.target[0] != data->player.y_pos
			|| data->ennemy.target[1] != data->player.x_pos
			|| !data->ennemy.path)
			pathfinding(data, data->map, (int)data->player.y_pos,
				(int)data->player.x_pos);
		move_ennemy(data);
	}
	get_move(data);
	raycasting(data);
	if (data->minimap_toggle)
		print_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
		data->mlx.frame.img, 0, 0);
}

int	execution(t_data *data)
{
	if (data->pause_menu.in_pause && !data->pause_menu.in_death
		&& !data->pause_menu.in_escape)
		pause_menu(data);
	else if (data->pause_menu.in_death)
		death_screen(data);
	else if (data->pause_menu.in_escape)
		escape_screen(data);
	else
		game_execution(data);
	return (1);
}
