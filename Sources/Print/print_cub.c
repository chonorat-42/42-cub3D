/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:50 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/01 13:41:49 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	print_cub(t_data *data)
{
	struct s_raycast	data_rc;

	init_raycast(&data_rc);
	get_move(data);
	raycasting(data, &data_rc);
	//print_minimap(data);
	return (1);
}
