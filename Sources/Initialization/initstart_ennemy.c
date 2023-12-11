/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstart_ennemy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:03:35 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/08 15:24:08 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initstart_ennemy(t_data *data)
{
	data->ennemy.pos[0] = 1;
	data->ennemy.pos[1] = 10;
	data->ennemy.dup_map = NULL;
	data->ennemy.d_pos[0] = data->ennemy.pos[0] + 0.5;
	data->ennemy.d_pos[1] = data->ennemy.pos[1] + 0.5;
	data->ennemy.target[0] = 0;
	data->ennemy.target[1] = 0;
}