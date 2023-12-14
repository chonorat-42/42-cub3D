/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:48:25 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/14 17:24:19 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	update_arr(unsigned long long **arr, size_t *res)
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

size_t	smallest(unsigned long long **arr, t_ennemy ennemy,
	int y, int x)
{
	size_t	res;
	size_t	i;

	(void)ennemy;
	(void)y;
	(void)x;
	update_arr(arr, &res);
	i = 0;
	while (i < 8)
	{
		if (arr[1][i] == 1)
		{
			res = arr[0][i];
		}
		i++;
	}
	return (res);
}
