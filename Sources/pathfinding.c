/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:53:34 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/04 19:42:27 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	difference(double a, double b)
{
	long long result;

	result = a - b;
	if (result < 0)
		result *= -1;

	// printf("a = %lf, b = %lf\n", a, b);
	// printf("res diff = %lld\n", result);

	return (result);
}

unsigned long long smallest(unsigned long long n, unsigned long long w, unsigned long long e, unsigned long long s)
{
	 unsigned long long res;

	 res = n;
	 if (w < res)
	 	res = w;
	if (e < res)
		res = e;
	if (s < res)
		res = s;
	return (res);
}

char best_path(char **map, int *pos, size_t y, size_t x)
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
	// printf("n = %llu, s = %llu, e = %llu, w = %llu\n", n, s, e, w);
	unsigned long long res = smallest(n, w, e, s);

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

void	solve_maze(char **map, double y, double x)
{
	int pos[2];
	char	c;

	pos[0] = 2;
	pos[1] = 19;
	map[pos[0]][pos[1]] = 'X';
	map[(int)y][(int)x] = 'P';

	// printf("player x = %lf, y = %lf\n", x, y);
	// printf("ennemy x = %d, y = %d\n", pos[1], pos[0]);
	print_arr(map);
	while (difference(pos[0], y) && difference(pos[1], x))
	{
		c = best_path(map, pos, (size_t)y, (size_t)x);
		if (c == 'n')
			pos[0]--;
		if (c == 's')
			pos[0]++;
		if (c == 'e')
			pos[1]++;
		if (c == 'w')
			pos[1]--;
		map[pos[0]][pos[1]] = '!';
		print_arr(map);
	}
}
