/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_algorithm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:57:54 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/04 15:14:37 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_east(t_data *data, t_flood **flood, t_flood *temp, char **map)
{
	size_t	j;
	size_t	i;

	j = temp->y;
	i = temp->x;
	if (map[j][i + 1] && !ft_ischarinset(map[j][i + 1], "W?"))
	{
		i++;
		map[j][i] = 'W';
		if (add_to_flood(flood, j, i))
			return (free_data(data), free_flood(flood), exit(1));
	}
}

static void	move_south(t_data *data, t_flood **flood, t_flood *temp, char **map)
{
	size_t	j;
	size_t	i;

	j = temp->y;
	i = temp->x;
	if (map[j + 1] && !ft_ischarinset(map[j + 1][i], "W?"))
	{
		j++;
		map[j][i] = 'W';
		if (add_to_flood(flood, j, i))
			return (free_data(data), free_flood(flood), exit(1));
	}
}

static void	move_west(t_data *data, t_flood **flood, t_flood *temp, char **map)
{
	size_t	j;
	size_t	i;

	j = temp->y;
	i = temp->x;
	if (i && !ft_ischarinset(map[j][i - 1], "W?"))
	{
		i--;
		map[j][i] = 'W';
		if (add_to_flood(flood, j, i))
			return (free_data(data), free_flood(flood), exit(1));
	}
}

static void	move_north(t_data *data, t_flood **flood, t_flood *temp, char **map)
{
	size_t	j;
	size_t	i;

	j = temp->y;
	i = temp->x;
	if (j && !ft_ischarinset(map[j - 1][i], "W?"))
	{
		j--;
		map[j][i] = 'W';
		if (add_to_flood(flood, j, i))
			return (free_data(data), free_flood(flood), exit(1));
	}
}

void	iterative_flood(t_data *data, char **map)
{
	t_flood	*flood;
	t_flood	*new_flood;
	t_flood	*temp;

	flood = NULL;
	first_position(data, &flood, map);
	while (flood)
	{
		temp = flood;
		new_flood = NULL;
		while (temp)
		{
			move_east(data, &new_flood, temp, map);
			move_south(data, &new_flood, temp, map);
			move_west(data, &new_flood, temp, map);
			move_north(data, &new_flood, temp, map);
			temp = temp->next;
		}
		free_flood(&flood);
		flood = new_flood;
	}
}
