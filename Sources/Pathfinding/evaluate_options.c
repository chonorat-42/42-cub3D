/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:58:37 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/14 14:48:17 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	evaluate_east(t_data *data, unsigned long long **arr, int y, int x)
{
	if (data->ennemy.dup_map[data->ennemy.pos[0]][data->ennemy.pos[1] + 1]
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0]]
			[data->ennemy.pos[1] + 1], "1?!V"))
		arr[0][E] = pow(difference(data->ennemy.pos[0], y), 2)
			+ pow(difference(data->ennemy.pos[1] + 1, x), 2);
	else
		arr[0][E] = MAX;
}

static void	evaluate_west(t_data *data, unsigned long long **arr, int y, int x)
{
	if (data->ennemy.dup_map[data->ennemy.pos[0]][data->ennemy.pos[1] - 1]
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0]]
			[data->ennemy.pos[1] - 1], "1?!V"))
		arr[0][W] = pow(difference(data->ennemy.pos[0], y), 2)
			+ pow(difference(data->ennemy.pos[1] - 1, x), 2);
	else
		arr[0][W] = MAX;
}

void	evaluate_options(t_data *data, unsigned long long **arr, int y, int x)
{
	evaluate_north(data, arr, y, x);
	evaluate_south(data, arr, y, x);
	evaluate_west(data, arr, y, x);
	evaluate_east(data, arr, y, x);
}
