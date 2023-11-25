/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/25 23:00:30 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	**getTempMap(void)
{
	char	**temp = NULL;
	int		index = 0;

	temp = malloc(sizeof(char *) * 11);
	temp[index++] = ft_strdup("1111111111111111111111111111111111111111");
	while (index < 8)
		temp[index++] = ft_strdup("1000000000000000000000000000000000000001");
	temp[index++] = ft_strdup("1000000010000000000N00000000000000000001");
	temp[index++] = ft_strdup("1111111111111111111111111111111111111111");
	temp[index] = NULL;
	return (temp);
}

int	print_cub(t_data *data)
{
	data->map = getTempMap();
	move_player(data);
	print_minimap(data, data->map);
	print_player(data, 0.25 * (data->screen_res[1] >> 7), (int)0xff0000);
	return (1);
}
