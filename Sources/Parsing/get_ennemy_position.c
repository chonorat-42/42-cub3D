/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ennemy_position.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:39:45 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/11 18:15:32 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ennemy_present(char **map, t_data *data)
{
	size_t	j;
	size_t	i;

	j = 0;
	data->ennemy.pres = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (ft_ischarinset(map[j][i], "X"))
			{
				data->ennemy.pres++;
				data->ennemy.pos[0] = j;
				data->ennemy.pos[1] = i;
			}
			i++;
		}
		j++;
	}
	if (!data->ennemy.pres)
		return (0);
	if (data->ennemy.pres > 1)
		return (print_error(PARSING, DPX), free_data(data), 0);
	return (1);
}

void	get_ennemy_position(t_data *data)
{
	if (!ennemy_present(data->parser.map, data))
		return ;
}
