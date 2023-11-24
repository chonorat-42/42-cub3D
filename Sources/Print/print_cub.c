/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/24 18:20:18 by chonorat         ###   ########lyon.fr   */
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

// static void	print_map(char **map)
// {
// 	int	index = 0;

// 	while (map[index])
// 		printf("%s\n", map[index++]);
// }

int	print_cub(t_data *data)
{
	char	**map = NULL;

	map = getTempMap();
	//data->player.dir = 90 * (M_PI / 180);
	//print_map(map);
	print_minimap(data, map);
	print_player(data);
	return (1);
}
