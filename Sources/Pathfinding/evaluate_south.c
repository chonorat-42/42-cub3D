/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_south.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:25:05 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/14 16:26:47 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	evaluate_se(t_data *data, unsigned long long **arr, int y, int x)
{
	if (data->ennemy.dup_map[data->ennemy.pos[0] + 1]
		&& data->ennemy.dup_map[0][data->ennemy.pos[1] + 1]
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0] + 1]
			[data->ennemy.pos[1] + 1], "1?!V")
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0]]
			[data->ennemy.pos[1] + 1], "1?!V"))
		arr[0][SE] = pow(difference(data->ennemy.pos[0] + 1, y), 2)
			+ pow(difference(data->ennemy.pos[1] + 1, x), 2);
	else
		arr[0][SE] = MAX;
}

void	evaluate_sw(t_data *data, unsigned long long **arr, int y, int x)
{
	if (data->ennemy.dup_map[data->ennemy.pos[0] + 1]
		&& data->ennemy.pos[1]
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0] + 1]
			[data->ennemy.pos[1] - 1], "1?!V")
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0]]
			[data->ennemy.pos[1] - 1], "1?!V"))
		arr[0][SW] = pow(difference(data->ennemy.pos[0] - 1, y), 2)
			+ pow(difference(data->ennemy.pos[1] - 1, x), 2);
	else
		arr[0][SW] = MAX;
}

void	evaluate_south(t_data *data, unsigned long long **arr, int y, int x)
{
	if (data->ennemy.dup_map[data->ennemy.pos[0] + 1]
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0] + 1]
			[data->ennemy.pos[1]], "1?!V"))
	{
		arr[0][S] = pow(difference(data->ennemy.pos[0] + 1, y), 2)
			+ pow(difference(data->ennemy.pos[1], x), 2);
		evaluate_se(data, arr, y, x);
		evaluate_sw(data, arr, y, x);
	}
	else
	{
		arr[0][S] = MAX;
		arr[0][SW] = MAX;
		arr[0][SE] = MAX;
	}
}
