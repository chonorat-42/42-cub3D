/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:59:39 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/01 12:05:00 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_flood(t_flood **flood)
{
	t_flood	*temp;

	temp = *flood;
	if (!temp->next)
	{
		free(*flood);
		*flood = NULL;
		return ;
	}
	while (*flood)
	{
		temp = *flood;
		*flood = temp->next;
		free(temp);
	}
	*flood = NULL;
}

int	add_to_flood(t_flood **flood, size_t j, size_t i)
{
	t_flood	*new;
	t_flood	*temp;

	new = malloc(sizeof(*new));
	if (!new)
		return (print_error(MALLOC, 0), 1);
	new->y = j;
	new->x = i;
	new->next = NULL;
	if (!*flood)
		*flood = new;
	else
	{
		temp = *flood;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

void	first_position(t_data *data, t_flood **flood, char **map)
{
	size_t	i;

	i = 0;
	while (map[0][i] && map[0][i] == '?')
		i++;
	if (add_to_flood(flood, 0, i))
		return (free_data(data), free_flood(flood), exit(1));
}
