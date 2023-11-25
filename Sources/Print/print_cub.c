/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/25 21:40:04 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	**getTempMap(void)
{
	char	**temp = NULL;
	int		index = 0;

	temp = malloc(sizeof(char *) * 11);
	temp[index++] = ft_strdup("1111111111111111111111111111111111111111");
	while (index < 8)
		temp[index++] = ft_strdup("1000000000000000000000000000000000000001");
	temp[index++] = ft_strdup("1000000010000000000N00000000000000000001");
	temp[index++] = ft_strdup("1111111111111111111111111111111111111111");
	temp[index] = NULL;
	return (temp);
}

static void	move_player(t_data *data)
{
	if (data->player.move.l_move)
	{
		if (data->player.move.sprint)
			data->player.x_pos -= 0.03;
		else
			data->player.x_pos -= 0.015;
	}
	if (data->player.move.r_move)
	{
		if (data->player.move.sprint)
			data->player.x_pos += 0.03;
		else
			data->player.x_pos += 0.015;
	}
	if (data->player.move.f_move)
	{
		if (data->player.move.sprint)
			data->player.y_pos -= 0.03;
		else
			data->player.y_pos -= 0.015;
	}
	if (data->player.move.b_move)
	{
		if (data->player.move.sprint)
			data->player.y_pos += 0.03;
		else
			data->player.y_pos += 0.015;
	}
}

int	print_cub(t_data *data)
{
	char	**map = NULL;

	map = getTempMap();
	move_player(data);
	print_minimap(data, map);
	print_player(data, 0.25 * (data->screen_res[1] >> 7), (int)0xff0000);
	ft_free_arr(map);
	return (1);
}
