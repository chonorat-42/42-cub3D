/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:41:41 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/24 15:44:36 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(char **map)
{
	int	index;

	index = 0;
	while (map[index])
		free(map[index++]);
	free(map);
}

void	free_data(t_data *data)
{
	if (data->mlx.mlx)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
}
