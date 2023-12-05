/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:53:34 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/05 16:44:29 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	difference(int a, int b)
{
	long long result;

	result = a - b;
	if (result < 0)
		result *= -1;

	// printf("a = %d, b = %d\n", a, b);
	// printf("res diff = %lld\n", result);

	return (result);
}

long long get_map_value(int **mask, size_t i, int y, int x)
{
	long long value;

	if (i == 0)
		value = mask[y -1][x];
	if (i == 1)
		value = mask[y][x - 1];
	if (i == 2)
		value = mask[y][x + 1];
	else
		value = mask[y - 1][x];
	return (value);
}

unsigned long long smallest(unsigned long long n, unsigned long long w, unsigned long long e, unsigned long long s, t_ennemy ennemy, int **mask, int y, int x)
{
	unsigned long long res;
	unsigned long long tab[2][4];
	long long value;

	(void)ennemy;
	tab[0][0] = n;
	tab[0][1] = w;
	tab[0][2] = e;
	tab[0][3] = s;

	res = n;
	if (w < res)
		res = w;
	if (w < res)
		res = w;
	if (e < res)
		res = e;
	if (s < res)
		res = s;
	size_t i = 0;
	while (i < 4)
	{
		tab[1][i] = 0;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (tab[0][i] == res)
			tab[1][i] = 1;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (tab[1][i] == 1)
		{
			res = tab[0][i];
			value = get_map_value(mask, i, y, x);
		}
		i++;
	}
	while (i < 4)
	{
		if (tab[1][i] == 1)
		{
			if (get_map_value(mask, i, y, x) < value)
			{
				value = get_map_value(mask, i, y, x);
				res = tab[0][i];
			}
		}
	}
	return (res);
}

void	print_mask(int **mask, size_t len, size_t height)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (j < height)
	{
		i = 0;
		while (i < len)
		{
			printf("%d", mask[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
	printf("\n");
}

void	clean_mask(int **mask, size_t height, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < len)
		{
			if (mask[j][i] != 0 && mask[j][i] != 1)
				mask[j][i] = 1;
			i++;
		}
		j++;
	}
}
/*if egalite -> go sur case avec la plus petite valeur*/

char best_path(t_data *data, char **map, int *pos, int y, int x, t_ennemy ennemy, int **mask)
{
	(void)data;
	unsigned long long	n, w, e, s;

	if (pos[0] && !ft_ischarinset(map[pos[0] - 1][pos[1]], "1?!"))
		n = (long long)pow(difference(pos[0] - 1, y), 2) + (long long)pow(difference(pos[1], x), 2);
	else
		n = 18446744073709551;
	if (map[pos[0] + 1] && !ft_ischarinset(map[pos[0] + 1][pos[1]], "1?!"))
		s = (long long)pow(difference(pos[0] + 1, y), 2) + (long long)pow(difference(pos[1], x), 2);
	else
		s = 18446744073709551;
	if (map[pos[0]][pos[1] + 1] && !ft_ischarinset(map[pos[0]][pos[1] + 1], "1?!"))
		e = (long long)pow(difference(pos[0], y), 2) + (long long)pow(difference(pos[1] + 1, x), 2);
	else
		e = 18446744073709551;
	if (pos[1] && !ft_ischarinset(map[pos[0]][pos[1] - 1], "1?!"))
		w = (long long)pow(difference(pos[0], y), 2) + (long long)pow(difference(pos[1] - 1, x), 2);
	else
		w = 18446744073709551;
	// printf("n = %llu, s = %llu, e = %llu, w = %llu\n", n, s, e, w);
	unsigned long long res = smallest(n, w, e, s, ennemy, mask, y, x);
	if (res == 18446744073709551)
	{
		// clean_mask(data->ennemy.mask, data->ennemy.height, data->ennemy.len);
		return ('k');
	}
	if (res == n)
		return ('n');
	if (res == s)
		return ('s');
	if (res == e)
		return ('e');
	else
		return ('w');
}

void	fill_mask(int **mask, char **map)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0')
				mask[j][i] = 1;
			else
				mask[j][i] = 0;
			i++;
		}
		j++;
	}
}

void	solve_maze(t_data *data, char **map, int y, int x)
{
	data->ennemy.height = ft_arr_size(map);
	data->ennemy.len = ft_strlen(map[0]);
	print_arr(map);
	data->ennemy.mask = malloc(sizeof(int *) * ft_arr_size(map));
	size_t	j = 0;
	while (j < data->ennemy.height)
	{
		data->ennemy.mask[j] = malloc(sizeof(int) * data->ennemy.len);
		j++;
	}
	fill_mask(data->ennemy.mask, map);
	print_mask(data->ennemy.mask, ft_strlen(map[0]), ft_arr_size(map));
	data->ennemy.pos[0] = 2;
	data->ennemy.pos[1] = 3;
	data->ennemy.d_pos[0] = data->ennemy.pos[0] + 0.5;
	data->ennemy.d_pos[1] = data->ennemy.pos[1] + 0.5;
	// printf("ennemy x = %d, y = %d\n", data->ennemy.pos[1], data->ennemy.pos[0]);
	// return ;

	char	c;
	map[data->ennemy.pos[0]][data->ennemy.pos[1]] = 'X';
	map[(int)y][(int)x] = 'P';

	// printf("player x = %d, y = %d, int x = %d, int y = %d\n", x, y, x, y);
	// printf("ennemy x = %d, y = %d\n", ennemy.pos[1], ennemy.pos[0]);
	data->player.l_pos[0] = (int)data->player.y_pos;
	data->player.l_pos[1] = (int)data->player.x_pos;
	// return ;
	while ((difference(data->ennemy.pos[0], y)) + (difference(data->ennemy.pos[1], x)))
	{
		// printf("diff y = %d, x = %d\n", data->ennemy.pos[0] - y, data->ennemy.pos[1] - x);
		c = best_path(data, map, data->ennemy.pos, y, x, data->ennemy, data->ennemy.mask);
		if (c == 'n')
		{
			data->ennemy.pos[0]--;
			// ennemy.last = NORTH;
		}
		if (c == 's')
		{
			data->ennemy.pos[0]++;
			// ennemy.last = SOUTH;
		}
		if (c == 'e')
		{
			data->ennemy.pos[1]++;
			// ennemy.last = EAST;
		}
		if (c == 'w')
		{
			data->ennemy.pos[1]--;
			// ennemy.last = WEST;
		}
		if (c == 'k')
			return ;
		data->ennemy.d_pos[0] = data->ennemy.pos[0] + 0.5;
		data->ennemy.d_pos[1] = data->ennemy.pos[1] + 0.5;
		map[data->ennemy.pos[0]][data->ennemy.pos[1]] = '!';
		data->ennemy.mask[data->ennemy.pos[0]][data->ennemy.pos[1]]++;
		if (data->ennemy.mask[data->ennemy.pos[0]][data->ennemy.pos[1]] >= 9)
			data->ennemy.mask[data->ennemy.pos[0]][data->ennemy.pos[1]] = 0;
		print_arr(map);
		print_mask(data->ennemy.mask, data->ennemy.len, data->ennemy.height);
		// printf("player x = %d, y = %d\n", (int)x, (int)y);
	}
	print_arr(map);
	print_mask(data->ennemy.mask, data->ennemy.len, data->ennemy.height);
}
