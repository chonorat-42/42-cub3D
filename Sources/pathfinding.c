/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:53:34 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/07 16:36:46 by chonorat         ###   ########lyon.fr   */
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

unsigned long long smallest(unsigned long long **arr, t_ennemy ennemy, int y, int x)
{
	unsigned long long	res;
	long long 			value;
	size_t 				i;


	i = 1;
	res = arr[0][0];
	while (i <= SW)
	{
		if (arr[0][i] < res)
			res = arr[0][i];
		i++;
	}
	i = 0;
	while (i < 8)
	{
		arr[1][i] = 0;
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (arr[0][i] == res)
			arr[1][i] = 1;
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (arr[1][i] == 1)
		{
			res = arr[0][i];
			value = get_map_value(ennemy.mask, i, y, x);
		}
		i++;
	}
	while (i < 8)
	{
		if (arr[1][i] == 1)
		{
			if (get_map_value(ennemy.mask, i, y, x) < value)
			{
				value = get_map_value(ennemy.mask, i, y, x);
				res = arr[0][i];
			}
		}
		i++;
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

void	print_int_arr(unsigned long long **arr, int line, int max)
{
	int i;

	i = 0;
	while (i < max)
	{
		printf("arr[%d][%d] = %lld\n", line, i, arr[line][i]);
		i++;
	}
}

void	free_ull(unsigned long long **arr, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
/*if egalite -> go sur case avec la plus petite valeur*/

int best_path(t_data *data, int y, int x, t_ennemy *ennemy)
{
	unsigned long long	**arr;
	size_t				i;

	arr = malloc(sizeof(unsigned long long*) * 2);
	if (!arr)
		return (free_data(data), print_error(MALLOC, 0), exit(1), 1);
	arr[0] = malloc(sizeof(unsigned long long) * 8);
	if (!arr[0])
		return (free_data(data), print_error(MALLOC, 0), free(arr), exit(1), 1);
	arr[1] = malloc(sizeof(unsigned long long) * 8);
	if (!arr[1])
		return (free_data(data), print_error(MALLOC, 0), free(arr), exit(1), 1);


	if (ennemy->pos[0] && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0] - 1][ennemy->pos[1]], "1?!"))
	{
		arr[0][NORTH] = (long long)pow(difference(ennemy->pos[0] - 1, y), 2) + (long long)pow(difference(ennemy->pos[1], x), 2);
		if (ennemy->pos[0] && data->ennemy.dup_map[0][ennemy->pos[1] + 1] && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0] - 1][ennemy->pos[1] + 1], "1?!") && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0]][ennemy->pos[1] + 1], "1?!"))
			arr[0][NE] = (long long)pow(difference(ennemy->pos[0] - 1, y), 2) + (long long)pow(difference(ennemy->pos[1] + 1, x), 2);
		else
			arr[0][NE] = 18446744073709551;
		if (ennemy->pos[0] && ennemy->pos[1] - 1 && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0] - 1][ennemy->pos[1] - 1], "1?!") && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0]][ennemy->pos[1] - 1], "1?!"))
			arr[0][NW] = (long long)pow(difference(ennemy->pos[0] - 1, y), 2) + (long long)pow(difference(ennemy->pos[1] - 1, x), 2);
		else
			arr[0][NW] = 18446744073709551;
	}
	else
	{
		arr[0][NORTH] = 18446744073709551;
		arr[0][NE] = 18446744073709551;
		arr[0][NW] = 18446744073709551;
	}


	if (data->ennemy.dup_map[ennemy->pos[0] + 1] && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0] + 1][ennemy->pos[1]], "1?!"))
	{
		arr[0][SOUTH] = (long long)pow(difference(ennemy->pos[0] + 1, y), 2) + (long long)pow(difference(ennemy->pos[1], x), 2);
		if (data->ennemy.dup_map[ennemy->pos[0] + 1] && data->ennemy.dup_map[0][ennemy->pos[1] + 1] && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0] + 1][ennemy->pos[1] + 1], "1?!") && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0]][ennemy->pos[1] + 1], "1?!"))
			arr[0][SE] = (long long)pow(difference(ennemy->pos[0] + 1, y), 2) + (long long)pow(difference(ennemy->pos[1] + 1, x), 2);
		else
			arr[0][SE] = 18446744073709551;
		if (data->ennemy.dup_map[ennemy->pos[0] + 1] && ennemy->pos[1] && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0] + 1][ennemy->pos[1] - 1], "1?!") && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0]][ennemy->pos[1] - 1], "1?!"))
			arr[0][SW] = (long long)pow(difference(ennemy->pos[0] - 1, y), 2) + (long long)pow(difference(ennemy->pos[1] - 1, x), 2);
		else
			arr[0][SW] = 18446744073709551;
	}
	else
	{
		arr[0][SOUTH] = 18446744073709551;
		arr[0][SW] = 18446744073709551;
		arr[0][SE] = 18446744073709551;
	}

	if (data->ennemy.dup_map[ennemy->pos[0]][ennemy->pos[1] + 1] && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0]][ennemy->pos[1] + 1], "1?!"))
		arr[0][EAST] = (long long)pow(difference(ennemy->pos[0], y), 2) + (long long)pow(difference(ennemy->pos[1] + 1, x), 2);
	else
		arr[0][EAST] = 18446744073709551;


	if (ennemy->pos[1] && !ft_ischarinset(data->ennemy.dup_map[ennemy->pos[0]][ennemy->pos[1] - 1], "1?!"))
		arr[0][WEST] = (long long)pow(difference(ennemy->pos[0], y), 2) + (long long)pow(difference(ennemy->pos[1] - 1, x), 2);
	else
		arr[0][WEST] = 18446744073709551;

	print_int_arr(arr, 0, 8);
	// printf("n = %llu, s = %llu, e = %llu, w = %llu\n", n, s, e, w);
	unsigned long long res = smallest(arr, *ennemy, y, x);
	printf("res = %lld\n", res);
	if (res == 18446744073709551)
	{
		clean_mask(data->ennemy.mask, data->ennemy.height, data->ennemy.len);
		return (free_ull(arr, 2), 'k');
	}
	i = 0;
	while (i < 8 && arr[0][i] != res)
		i++;
	return (free_ull(arr, 2), i);

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

void	init_ennemy(t_data *data, t_ennemy *ennemy, char **map)
{
	size_t	j;

	j = 0;
	ennemy->target[0] = data->player.y_pos;
	ennemy->target[1] = data->player.x_pos;
	ennemy->height = ft_arr_size(map);
	ennemy->len = ft_strlen(map[0]);
	ennemy->mask = malloc(sizeof(int *) * ft_arr_size(map));
	ennemy->path = NULL;
	while (j < ennemy->height)
	{
		ennemy->mask[j] = malloc(sizeof(int) * ennemy->len);
		j++;
	}
	fill_mask(ennemy->mask, map);
	// printf("ennemy x = %d, y = %d\n", data->ennemy.pos[1], data->ennemy.pos[0]);
	map[ennemy->pos[0]][ennemy->pos[1]] = 'X';
	// map[(int)y][(int)x] = 'P';
	// printf("player x = %d, y = %d, int x = %d, int y = %d\n", x, y, x, y);
	// printf("ennemy x = %d, y = %d\n", ennemy.pos[1], ennemy.pos[0]);
	data->player.l_pos[0] = (int)data->player.y_pos;
	data->player.l_pos[1] = (int)data->player.x_pos;
}

void	update_ennemy(t_data *data)
{
	//data->ennemy.d_pos[0] = data->ennemy.pos[0] + 0.5;
	//data->ennemy.d_pos[1] = data->ennemy.pos[1] + 0.5;
	printf("x = %d, y = %d\n", data->ennemy.pos[1], data->ennemy.pos[0]);
	data->ennemy.dup_map[data->ennemy.pos[0]][data->ennemy.pos[1]] = '!';
	data->ennemy.mask[data->ennemy.pos[0]][data->ennemy.pos[1]]++;
	if (data->ennemy.mask[data->ennemy.pos[0]][data->ennemy.pos[1]] >= 9)
		data->ennemy.mask[data->ennemy.pos[0]][data->ennemy.pos[1]] = 0;
}

void	add_path(t_data *data, t_path **path, int y, int x)
{
	t_path	*temp;
	t_path	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (print_error(MALLOC, 0), free_data(data), exit(1));
	new->next = NULL;
	new->coor[0] = y + 0.5;
	new->coor[1] = x + 0.5;
	if (!*path)
		*path = new;
	else
	{
		temp = *path;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	new->head = *path;
}

void	print_coor(t_path *path)
{
	t_path *temp;
	size_t	i;

	i = 0;
	temp = path;
	while (temp)
	{
		printf("path %zu, y = %d, x = %d\n", i, (int)temp->coor[0], (int)temp->coor[1]);
		i++;
		temp = temp->next;
	}
}

void	solve_maze(t_data *data, char **map, int y, int x)
{
	char	c;

	if (data->ennemy.dup_map)
	{
		ft_free_arr(data->ennemy.dup_map);
		data->ennemy.dup_map = ft_arr_copy(map);
	}
	data->ennemy.dup_map = ft_arr_copy(map);
	init_ennemy(data, &data->ennemy, data->ennemy.dup_map);
	data->ennemy.dup_map[y][x] = 'P';
	print_arr(data->ennemy.dup_map);
	while ((difference(data->ennemy.pos[0], y)) + (difference(data->ennemy.pos[1], x)))
	{
		c = best_path(data, y, x, &data->ennemy);
		printf("c = %d\n", c);
		if (c == NORTH)
			add_path(data, &data->ennemy.path, data->ennemy.pos[0]--, data->ennemy.pos[1]);
		if (c == SOUTH)
			add_path(data, &data->ennemy.path, data->ennemy.pos[0]++, data->ennemy.pos[1]);
		if (c == EAST)
			add_path(data, &data->ennemy.path, data->ennemy.pos[0], data->ennemy.pos[1]++);
		if (c == WEST)
			add_path(data, &data->ennemy.path, data->ennemy.pos[0], data->ennemy.pos[1]--);
		if (c == NE)
			add_path(data, &data->ennemy.path, data->ennemy.pos[0]--, data->ennemy.pos[1]++);
		if (c == NW)
			add_path(data, &data->ennemy.path, data->ennemy.pos[0]--, data->ennemy.pos[1]--);
		if (c == SE)
			add_path(data, &data->ennemy.path, data->ennemy.pos[0]++, data->ennemy.pos[1]++);
		if (c == SW)
			add_path(data, &data->ennemy.path, data->ennemy.pos[0]++, data->ennemy.pos[1]--);
		if (c == 'k')
		{
			clean_mask(data->ennemy.mask, data->ennemy.height, data->ennemy.len);
			return ;
		}
		update_ennemy(data);
		print_arr(data->ennemy.dup_map);
		// print_mask(data->ennemy.mask, data->ennemy.len, data->ennemy.height);
		// printf("player x = %d, y = %d\n", (int)x, (int)y);
	}
	data->ennemy.dup_map[y][x] = 'P';
	print_arr(data->ennemy.dup_map);
	print_coor(data->ennemy.path);
	// // print_mask(data->ennemy.mask, data->ennemy.len, data->ennemy.height);
}
