/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:48:25 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/08 12:47:57 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static long long	get_map_value(int **mask, size_t i, int y, int x)
{
	long long	value;

	if (i == 0)
		value = mask[y -1][x];
	if (i == 1)
		value = mask[y][x - 1];
	if (i == 2)
		value = mask[y][x + 1];
	else
		value = mask[y - 1][x];
	return (value);
}

static void	update_arr(unsigned long long **arr, unsigned long long *res)
{
	size_t	i;

	i = 0;
	*res = arr[0][0];
	while (i <= SW)
	{
		if (arr[0][i] < *res)
			*res = arr[0][i];
		i++;
	}
	i = 0;
	while (i < 8)
	{
		arr[1][i] = 0;
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (arr[0][i] == *res)
			arr[1][i] = 1;
		i++;
	}
}

unsigned long long	smallest(unsigned long long **arr, t_ennemy ennemy,
	int y, int x)
{
	unsigned long long	res;
	long long			value;
	size_t				i;

	update_arr(arr, &res);
	i = 0;
	while (i < 8)
	{
		if (arr[1][i] == 1)
		{
			if (get_map_value(ennemy.mask, i, y, x) < value)
			{
				value = get_map_value(ennemy.mask, i, y, x);
				res = arr[0][i];
			}
		}
		i++;
	}
	return (res);
}
