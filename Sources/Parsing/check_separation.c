/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:58:07 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/01 14:21:11 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_after_diffusion(char **map)
{
	size_t	j;

	j = 0;
	while (map[j])
	{
		if (!ft_isstronlyset(map[j], "?W"))
			return (1);
		j++;
	}
	return (0);
}

int	is_map_separated(t_data *data, char **map)
{
	char	**dup;

	dup = ft_arr_copy(map);
	if (!dup)
		return (print_error(MALLOC, 0), ft_free_arr(dup), 1);
	iterative_flood(data, dup);
	if (check_after_diffusion(dup))
		return (print_error(PARSING, SEP), ft_free_arr(dup), 1);
	return (ft_free_arr(dup), 0);
}
