/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_north.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:22:56 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/08 12:24:00 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	evaluate_ne(t_data *data, unsigned long long **arr, int y, int x)
{
	if (data->ennemy.pos[0] && data->ennemy.dup_map[0]
		[data->ennemy.pos[1] + 1]
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0] - 1]
			[data->ennemy.pos[1] + 1], "1?!")
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0]]
			[data->ennemy.pos[1] + 1], "1?!"))
		arr[0][NE] = pow(difference(data->ennemy.pos[0] - 1, y),
				2) + pow(difference(data->ennemy.pos[1] + 1, x),
				2);
	else
		arr[0][NE] = MAX;
}

static void	evaluate_nw(t_data *data, unsigned long long **arr, int y, int x)
{
	if (data->ennemy.pos[0] && data->ennemy.pos[1] - 1
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0] - 1]
			[data->ennemy.pos[1] - 1], "1?!")
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0]]
			[data->ennemy.pos[1] - 1], "1?!"))
		arr[0][NW] = pow(difference(data->ennemy.pos[0] - 1, y), 2)
			+ pow(difference(data->ennemy.pos[1] - 1, x), 2);
	else
		arr[0][NW] = MAX;
}

void	evaluate_north(t_data *data, unsigned long long **arr, int y, int x)
{
	if (data->ennemy.pos[0]
		&& !ft_ischarinset(data->ennemy.dup_map[data->ennemy.pos[0] - 1]
			[data->ennemy.pos[1]], "1?!"))
	{
		arr[0][N] = pow(difference(data->ennemy.pos[0] - 1, y), 2)
			+ pow(difference(data->ennemy.pos[1], x), 2);
		evaluate_ne(data, arr, y, x);
		evaluate_nw(data, arr, y, x);
	}
	else
	{
		arr[0][N] = MAX;
		arr[0][NE] = MAX;
		arr[0][NW] = MAX;
	}
}
