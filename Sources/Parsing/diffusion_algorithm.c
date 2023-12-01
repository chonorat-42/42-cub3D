/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffusion_algorithm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:39:59 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/01 11:13:06 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_coor(t_flood *flood)
{
	t_flood *temp;

	temp = flood;
	while (temp)
	{
		printf("x = %zu, y = %zu\n", temp->x, temp->y);
		temp = temp->next;
	}
}

size_t	flood_size(t_flood *flood)
{
	t_flood *temp;
	size_t res;

	res = 0;
	temp = flood;
	while (temp)
	{
		res++;
		temp = temp->next;
	}
	return (res);
}

// static void mark_map(t_flood *flood, char **map)
// {
// 	t_flood *temp;

// 	// size_t size = flood_size(flood);
// 	// printf("%zu\n", size);

// 	temp = flood;
// 	while (temp)
// 	{
// 		map[flood->y][flood->x] = 'W';
// 		temp = temp->next;
// 	}
// 	print_arr(map);
// }

static void free_flood(t_flood **flood)
{
	t_flood *temp;

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

static int	add_to_flood(t_flood **flood, size_t j, size_t i)
{
	t_flood	*new;
	t_flood *temp;

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

// static void iterative_diffusion_algorithm(char **map)
// {
// 	t_flood *flood;
// 	size_t	j;
// 	size_t	i;
// 	size_t	diff;

// 	j = 0;
// 	i = 0;
// 	while (map[j][i] == '?')
// 		i++;
// 	flood = NULL;
// 	add_to_flood(&flood, j, i);
// 	map[j][i] = 'W';
// 	while (flood)
// 	{
// 		// mark_map(flood, map);
// 		free_flood(&flood);
// 		diff = 0;
// 		while (map[j][i + 1] && !ft_ischarinset(map[j][i + 1], "W?"))
// 		{
// 			add_to_flood(&flood, j, i + 1);
// 			i++;
// 			map[j][i] = 'W';
// 			diff++;
// 			diff = 0;
// 		}
// 		while (map[j + 1] && !ft_ischarinset(map[j + 1][i], "W?"))
// 		{
// 			add_to_flood(&flood, j + 1, i);
// 			j++;
// 			map[j][i] = 'W';
// 			diff++;
// 			// j += diff - 1;
// 			diff = 0;
// 		}
// 		while (j != 0 && !ft_ischarinset(map[j - 1][i], "W?"))
// 		{
// 			add_to_flood(&flood, j - 1, i);
// 			j--;
// 			map[j][i] = 'W';
// 			diff++;
// 			// i += diff - 1;
// 			diff = 0;
// 		}
// 		while (i - 1 != 0 && !ft_ischarinset(map[j][i--], "W?"))
// 		{
// 			add_to_flood(&flood, j, i - 1);
// 			i--;
// 			map[j][i] = 'W';
// 			diff++;
// 			// j -= diff - 1;
// 			diff = 0;
// 		}
// 		size_t	fsize = flood_size(flood);
// 		printf("size = %zu\n", fsize);
// 		print_coor(flood);
// 		print_arr(map);
// 	}
// }

// static void	diffusion_algorithm(char **map, size_t j, size_t i)
// {
// 	if (ft_ischarinset(map[j][i], "?W"))
// 		return ;
// 	else if (map[j][i] != '?')
// 	{
// 		map[j][i] = 'W';
// 		if (j != 0)
// 			diffusion_algorithm(map, j - 1, i);
// 		if (map[j + 1])
// 			diffusion_algorithm(map, j + 1, i);
// 		if (i != 0)
// 			diffusion_algorithm(map, j, i - 1);
// 		if (map[j][i + 1])
// 			diffusion_algorithm(map, j, i + 1);
// 	}
// 	return ;
// }

int	iterative_flood(char **map)
{
	size_t	j;
	size_t	i;
	t_flood *flood;
	t_flood *new_flood;
	t_flood *temp;

	j = 0;
	i = 0;
	while (map[j][i] && map[j][i] == '?')
		i++;
	flood = NULL;
	if (add_to_flood(&flood, j, i))
		return (1);
	while (flood)
	{
		temp = flood;
		new_flood = NULL;
		while (temp)
		{
			j = temp->y;
			i = temp->x;
			if (map[j][i + 1] && !ft_ischarinset(map[j][i + 1], "W?"))
			{
				i++;
				map[j][i] = 'W';
				if (add_to_flood(&new_flood, j, i))
					return (1);
			}
			j = temp->y;
			i = temp->x;
			if (map[j + 1] && !ft_ischarinset(map[j + 1][i], "W?"))
			{
				j++;
				map[j][i] = 'W';
				if (add_to_flood(&new_flood, j, i))
					return (1);
			}
			j = temp->y;
			i = temp->x;
			if (i && !ft_ischarinset(map[j][i - 1], "W?"))
			{
				i--;
				map[j][i] = 'W';
				if (add_to_flood(&new_flood, j, i))
					return (1);
			}
			j = temp->y;
			i = temp->x;
			if (j && !ft_ischarinset(map[j - 1][i], "W?"))
			{
				j--;
				map[j][i] = 'W';
				if (add_to_flood(&new_flood, j, i))
					return (1);
			}
			temp = temp->next;
			print_arr(map);
		}
		free_flood(&flood);
		flood = new_flood;
		printf("FLOOD EMPTIED\n");
	}
	return (0);
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
	// diffusion_algorithm(dup, 0, i);
	// iterative_diffusion_algorithm(dup);
	if (iterative_flood(dup))
		return (ft_free_arr(dup), 2);
	print_arr(dup);
	if (check_after_diffusion(dup))
		return (print_error(PARSING, SEP), ft_free_arr(dup), 1);
	return (ft_free_arr(dup), 0);
	return (0);
}
