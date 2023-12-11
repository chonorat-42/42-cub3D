/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:36:31 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/11 18:16:20 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ennemy(t_data *data, t_ennemy *ennemy, char **map)
{
	size_t	j;

	printf("ennemy y = %d, ennemy x = %d\n", ennemy->pos[0], ennemy->pos[1]);
	j = 0;
	ennemy->target[0] = data->player.y_pos;
	ennemy->target[1] = data->player.x_pos;
	ennemy->height = ft_arr_size(map);
	ennemy->len = ft_strlen(map[0]);
	ennemy->path = NULL;
	map[data->ennemy.pos[0]][data->ennemy.pos[1]] = 'X';
	data->player.l_pos[0] = (int)data->player.y_pos;
	data->player.l_pos[1] = (int)data->player.x_pos;
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
	printf("new_coor x = %f, y = %f\n", new->coor[1], new->coor[0]);
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

int	update_path(t_data *data, t_path **path, int c, int *pos)
{
	if (c == N)
		return (add_path(data, path, pos[0]--, pos[1]), 0);
	if (c == S)
		return (add_path(data, path, pos[0]++, pos[1]), 0);
	if (c == E)
		return (add_path(data, path, pos[0], pos[1]++), 0);
	if (c == W)
		return (add_path(data, path, pos[0], pos[1]--), 0);
	if (c == NE)
		return (add_path(data, path, pos[0]--, pos[1]++), 0);
	if (c == NW)
		return (add_path(data, path, pos[0]--, pos[1]--), 0);
	if (c == SE)
		return (add_path(data, path, pos[0]++, pos[1]++), 0);
	if (c == SW)
		return (add_path(data, path, pos[0]++, pos[1]--), 0);
	else
		return (1);
}
