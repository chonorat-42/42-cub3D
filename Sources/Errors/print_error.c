/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:05:18 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/21 12:42:31 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_error(int type, int error)
{
	(void)error;
	ft_dprintf(2, "%sError\n", RED);
	if (type == ARGC)
		ft_dprintf(2, "usage: ./cub3D Maps/map_name.cub\n%s", END);
}
