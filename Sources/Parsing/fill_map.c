/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:57:06 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/11 17:38:32 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	arr_malloc_ko(char **arr, size_t j)
{
	size_t	k;

	k = 0;
	while (k < j)
	{
		free(arr[k]);
		k++;
	}
	return (free(arr));
}

static int	fill_string(char **map, char *s, size_t j, size_t length)
{
	size_t	i;

	map[j] = malloc(sizeof(char) * (length + 1));
	if (!map[j])
		return (arr_malloc_ko(map, j), 1);
	map[j][length] = '\0';
	i = 0;
	while (s[i])
	{
		if (s[i] == '1' || s[i] == '0')
			map[j][i] = s[i];
		else if (ft_ischarinset(s[i], "NWSEX"))
			map[j][i] = '0';
		else
			map[j][i] = '?';
		i++;
	}
	while (i < length)
	{
		map[j][i] = '?';
		i++;
	}
	return (0);
}

static size_t	get_longest_line(char **arr)
{
	size_t	i;
	size_t	len;
	size_t	result;

	i = 0;
	result = 0;
	while (arr[i])
	{
		len = ft_strlen(arr[i]);
		if (len > result)
			result = len;
		i++;
	}
	return (result);
}

void	fill_map(t_data *data, t_parser *parser)
{
	size_t	size;
	size_t	i;
	size_t	length;

	size = ft_arr_size(parser->map);
	length = get_longest_line(parser->map);
	data->map = malloc(sizeof(char *) * (size + 1));
	if (!data->map)
		return (free_data(data), print_error(MALLOC, 0), exit(1));
	data->map[size] = NULL;
	i = 0;
	while (parser->map[i])
	{
		if (fill_string(data->map, parser->map[i], i, length))
			return (free_data(data), print_error(MALLOC, 0), exit(1));
		i++;
	}
}
