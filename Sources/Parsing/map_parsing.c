/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:57:47 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/28 13:02:40 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	player_position_found(t_data *data, int *found,
	long long i, long long j)
{
	if (!*found)
	{
		get_player_dir(data, i, j);
		data->player.x_pos = (double)i + 0.5;
		data->player.y_pos = (double)j + 0.5;
		(*found)++;
		return (0);
	}
	else
		return (print_error(PARSING, DPP), free_data(data), 1);
}

static void	get_player_position(t_data *data)
{
	long long	j;
	long long	i;
	int			found;

	j = -1;
	found = 0;
	while (data->parser.map[++j])
	{
		i = -1;
		while (data->parser.map[j][++i])
		{
			if (ft_ischarinset(data->parser.map[j][i], "NSEW"))
			{
				if (player_position_found(data, &found, i, j))
					exit(1);
			}
		}
	}
	if (found == 1)
		return ;
	return (print_error(PARSING, NOP), free_data(data), exit(1));
}

size_t	get_longest_line(char **arr)
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

void	map_parser(t_data *data, t_parser *parser)
{
	(void)parser;
	fill_map(data, parser);
	get_player_position(data);
	print_arr(data->map);
}
