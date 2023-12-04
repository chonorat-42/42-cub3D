/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:01:43 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/04 15:01:14 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	border_is_one(char **map, char *str, size_t j)
{
	size_t	k;
	size_t	l;

	if (j == 0 || !map[j + 1])
	{
		if (!ft_isstronlyset(map[j], "?1"))
			return (0);
		return (1);
	}
	k = 0;
	while (str[k] && ft_ischarinset(str[k], "?"))
		k++;
	if (str[k] != '1')
		return (1);
	l = ft_strlen(str) - 1;
	while (l && ft_ischarinset(str[l], "?"))
		l--;
	if (str[l] != '1')
		return (0);
	return (1);
}

static int	check_up_down(char **map, size_t i, size_t j)
{
	if (j != 0)
	{
		if (!ft_ischarinset(map[j - 1][i], "?1"))
			return (1);
	}
	if (map[j + 1])
	{
		if (!ft_ischarinset(map[j + 1][i], "?1"))
			return (1);
	}
	return (0);
}

static int	check_right_left(char **map, size_t i, size_t j)
{
	if (i != 0)
	{
		if (!ft_ischarinset(map[j][i - 1], "?1"))
			return (1);
	}
	if (!ft_ischarinset(map[j][i + 1], "?1") && map[j][i + 1] != '\0')
	{
		return (1);
	}
	return (0);
}

static int	are_space_bordered(char **map, size_t j,
	size_t beginning, size_t end)
{
	size_t	i;

	i = beginning;
	end = ft_strlen(map[j]);
	while (i < end)
	{
		if (map[j][i] == '?')
		{
			if (check_up_down(map, i, j))
				return (1);
			if (check_right_left(map, i, j))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_borders(char **map)
{
	size_t	j;
	size_t	beginning;
	size_t	end;

	j = 0;
	while (map[j])
	{
		if (!border_is_one(map, map[j], j))
			return (print_error(PARSING, BORD), 1);
		beginning = 0;
		end = ft_strlen(map[j]);
		while (map[j][beginning] == ' ')
			beginning++;
		if (are_space_bordered(map, j, beginning, end))
			return (print_error(PARSING, SPACEB), 1);
		j++;
	}
	return (0);
}
