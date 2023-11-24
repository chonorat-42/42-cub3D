/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/24 15:22:16 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	**getTempMap(void)
{
	char	**temp = NULL;
	int		index = 0;

	temp = malloc(sizeof(char *) * 11);
	temp[index++] = ft_strdup("1111111111111111111111111111111111111111");
	while (index < 9)
		temp[index++] = ft_strdup("1000000000000000000000000000000000000001");
	temp[index++] = ft_strdup("1111111111111111111111111111111111111111");
	temp[index] = NULL;
	return (temp);
}

static void	print_map(char **map)
{
	int	index = 0;

	while (map[index])
		printf("%s\n", map[index++]);
}

static void	free_map(char **map)
{
	int	index;

	index = 0;
	while (map[index])
		free(map[index++]);
	free(map);
}

void	print_cub(t_data *data)
{
	char	**map = NULL;

	map = getTempMap();
	print_map(map);
	print_minimap(data, map);
	free_map(map);
}
