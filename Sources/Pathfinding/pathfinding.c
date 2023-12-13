/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:53:34 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/13 20:25:48 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	print_mask(int **mask, size_t len, size_t height)
// {
// 	size_t	j;
// 	size_t	i;

// 	j = 0;
// 	i = 0;
// 	while (j < height)
// 	{
// 		i = 0;
// 		while (i < len)
// 		{
// 			printf("%d", mask[j][i]);
// 			i++;
// 		}
// 		printf("\n");
// 		j++;
// 	}
// 	printf("\n");
// }}

int	best_path(t_data *data, int y, int x, t_ennemy *ennemy)
{
	unsigned long long	**arr;
	size_t				i;
	unsigned long long	res;

	arr = malloc(sizeof(unsigned long long *) * 2);
	if (!arr)
		return (free_data(data), print_error(MALLOC, 0), exit(1), 1);
	arr[0] = malloc(sizeof(unsigned long long) * 8);
	if (!arr[0])
		return (free_data(data), print_error(MALLOC, 0),
			free_ull(arr, 2), exit(1), 1);
	arr[1] = malloc(sizeof(unsigned long long) * 8);
	if (!arr[1])
		return (free_data(data), print_error(MALLOC, 0),
			free_ull(arr, 2), exit(1), 1);
	evaluate_options(data, arr, y, x);
	res = smallest(arr, *ennemy, y, x);
	if (res == MAX)
		return (free_ull(arr, 2), 'k');
	i = 0;
	while (i < 8 && arr[0][i] != res)
		i++;
	return (free_ull(arr, 2), i);
}

int	last_is_close(t_path *path, int y, int x)
{
	t_path	*temp;

	temp = path;
	while (temp->next)
		temp = temp->next;
	if (difference(temp->coor[0], y) <= 1 && difference(temp->coor[1], x) <= 1)
		return (1);
	return (0);
}

void	pathfinding(t_data *data, char **map, int y, int x)
{
	int	c;

	c = 0;
	if (data->ennemy.dup_map)
		ft_free_arr(data->ennemy.dup_map);
	if (data->ennemy.path)
		free_path(&data->ennemy.path);
	data->ennemy.dup_map = ft_arr_copy(map);
	if (!data->ennemy.dup_map)
		return (print_error(MALLOC, 0), free_data(data), exit(1));
	init_ennemy(data, &data->ennemy, data->ennemy.dup_map);
	while ((difference(data->ennemy.pos[0], y))
		+ (difference(data->ennemy.pos[1], x)))
	{
		c = best_path(data, y, x, &data->ennemy);
		if (update_path(data, &data->ennemy.path, c, data->ennemy.pos))
			return ;
		data->ennemy.dup_map[data->ennemy.pos[0]]
		[data->ennemy.pos[1]] = '!';
	}
	if (last_is_close(data->ennemy.path, y, x))
		update_path(data, &data->ennemy.path, c, data->ennemy.pos);
	data->ennemy.dup_map[y][x] = 'P';
}
