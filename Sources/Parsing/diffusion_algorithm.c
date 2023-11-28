/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffusion_algorithm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:39:59 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/28 19:55:09 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void print_last(t_flood *flood, char **map)
{
	map[flood->y][flood->x] = 'W';
}

static void delete_last(t_flood **flood)
{

}

static void	add_to_flood(t_flood **flood, size_t j, size_t i)
{
	t_flood	*new;
	t_flood *temp;

	new = malloc(sizeof(*new));
	if (!new)
		return (print_error(MALLOC, 0));
	new->y = j;
	new->x = i;
	new->next = NULL;
	if (!flood)
		flood = new;
	else
	{
		new->next = flood;
		flood = new;
	}
}

static void iterative_diffusion_algorithm(char **map)
{
	t_flood *flood;
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (map[j][i] == '?')
		i++;
	add_to_flood(&flood, j, i);
	while (flood)
	{
		print_last(flood, map);
		delete_last(flood);
		if (j != 0 && ft_ischarinset(map[j - 1][i], "W?"))
			add_to_flood(flood, j - 1, i);
		if (map[j + 1] && ft_ischarinset(map[j + 1][i], "W?"))
			add_to_flood(flood, j + 1, i);
		if (i != 0 && ft_ischarinset(map[j][i - 1], "W?"))
			add_to_flood(flood, j, i - 1);
		if (map[j][i + 1] && ft_ischarinset(map[j][i + 1], "W?"))
			add_to_flood(flood, j, i + 1);
	}


}

static void	diffusion_algorithm(char **map, size_t j, size_t i)
{
	if (ft_ischarinset(map[j][i], "?W"))
		return ;
	else if (map[j][i] != '?')
	{
		map[j][i] = 'W';
		if (j != 0)
			diffusion_algorithm(map, j - 1, i);
		if (map[j + 1])
			diffusion_algorithm(map, j + 1, i);
		if (i != 0)
			diffusion_algorithm(map, j, i - 1);
		if (map[j][i + 1])
			diffusion_algorithm(map, j, i + 1);
	}
	return ;
}

static int	check_after_diffusion(char **map)
{
	size_t	j;

	j = 0;
	while (map[j])
	{
		if (!ft_isstronlyset(map[j], "?W"))
			return (1);
		j++;
	}
	return (0);
}

int	is_map_separated(char **map)
{
	char	**dup;
	size_t	i;

	dup = ft_arr_copy(map);
	if (!dup)
		return (print_error(MALLOC, 0), ft_free_arr(dup), 1);
	i = 0;
	while (map[0][i] == '?')
		i++;
	diffusion_algorithm(dup, (size_t)0, i);
	if (check_after_diffusion(dup))
		return (print_error(PARSING, SEP), ft_free_arr(dup), 1);
	return (ft_free_arr(dup), 0);
}
