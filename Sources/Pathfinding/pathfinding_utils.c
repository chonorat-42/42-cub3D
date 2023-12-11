/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:40:42 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/11 16:16:12 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	double_difference(double a, double b)
{
	double result;

	result = a - b;
	if (result < 0)
		result *= -1;
	return (result);
}

size_t	difference(int a, int b)
{
	long long	result;

	result = a - b;
	if (result < 0)
		result *= -1;
	return (result);
}

void	clean_mask(int **mask, size_t height, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < len)
		{
			if (mask[j][i] != 0 && mask[j][i] != 1)
				mask[j][i] = 1;
			i++;
		}
		j++;
	}
}

void	free_ull(unsigned long long **arr, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	fill_mask(int **mask, char **map)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0')
				mask[j][i] = 1;
			else
				mask[j][i] = 0;
			i++;
		}
		j++;
	}
}
