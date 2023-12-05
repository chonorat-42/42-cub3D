/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:53:34 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/05 11:16:16 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	difference(int a, int b)
{
	long long result;

	result = a - b;
	if (result < 0)
		result *= -1;

	printf("a = %d, b = %d\n", a, b);
	// printf("res diff = %lld\n", result);

	return (result);
}

unsigned long long smallest(unsigned long long n, unsigned long long w, unsigned long long e, unsigned long long s, t_ennemy ennemy)
{
	 unsigned long long res;

	if (ennemy.last == NORTH)
		res = n;
	if (ennemy.last == SOUTH)
		res = s;
	if (ennemy.last == EAST)
		res = e;
	if (ennemy.last == WEST)
		res = w;
	if (w < res)
		res = w;
	if (e < res)
		res = e;
	if (s < res)
		res = s;
	return (res);
}

char best_path(char **map, int *pos, int y, int x, t_ennemy ennemy)
{
	unsigned long long	n, w, e, s;

	if (pos[0] && !ft_ischarinset(map[pos[0] - 1][pos[1]], "1?"))
		n = (long long)pow(difference(pos[0] - 1, y), 2) + (long long)pow(difference(pos[1], x), 2);
	else
		n = 18446744073709551;
	if (map[pos[0] + 1] && !ft_ischarinset(map[pos[0] + 1][pos[1]], "1?"))
		s = (long long)pow(difference(pos[0] + 1, y), 2) + (long long)pow(difference(pos[1], x), 2);
	else
		s = 18446744073709551;
	if (map[pos[0]][pos[1] + 1] && !ft_ischarinset(map[pos[0]][pos[1] + 1], "1?"))
		e = (long long)pow(difference(pos[0], y), 2) + (long long)pow(difference(pos[1] + 1, x), 2);
	else
		e = 18446744073709551;
	if (pos[1] && !ft_ischarinset(map[pos[0]][pos[1] - 1], "1?"))
		w = (long long)pow(difference(pos[0], y), 2) + (long long)pow(difference(pos[1] - 1, x), 2);
	else
		w = 18446744073709551;
	printf("n = %llu, s = %llu, e = %llu, w = %llu\n", n, s, e, w);
	unsigned long long res = smallest(n, w, e, s, ennemy);

	// printf("res = %llu\n", res);

	if (res == n)
		return ('n');
	if (res == s)
		return ('s');
	if (res == e)
		return ('e');
	else
		return ('w');
}

void	solve_maze(char **map, int y, int x)
{
	t_ennemy ennemy;

	ennemy.pos[0] = 3;
	ennemy.pos[1] = 4;

	char	c;
	map[ennemy.pos[0]][ennemy.pos[1]] = 'X';
	map[(int)y][(int)x] = 'P';

	printf("player x = %d, y = %d, int x = %d, int y = %d\n", x, y, x, y);
	printf("ennemy x = %d, y = %d\n", ennemy.pos[1], ennemy.pos[0]);
	print_arr(map);
	while ((ennemy.pos[0] - y) + (ennemy.pos[1] - x))
	{
		printf("diff y = %d, x = %d\n", ennemy.pos[0] - y, ennemy.pos[1] - x);
		c = best_path(map, ennemy.pos, y, x, ennemy);
		if (c == 'n')
		{
			ennemy.pos[0]--;
			ennemy.last = NORTH;
		}
		if (c == 's')
		{
			ennemy.pos[0]++;
			ennemy.last = SOUTH;
		}
		if (c == 'e')
		{
			ennemy.pos[1]++;
			ennemy.last = EAST;
		}
		if (c == 'w')
		{
			ennemy.pos[1]--;
			ennemy.last = WEST;
		}
		map[ennemy.pos[0]][ennemy.pos[1]] = '!';
		print_arr(map);
		printf("player x = %d, y = %d\n", (int)x, (int)y);
		printf("ennemy x = %d, y = %d\n", ennemy.pos[1], ennemy.pos[0]);
	}
}
