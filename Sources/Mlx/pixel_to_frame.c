/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_to_frame.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:48:24 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/17 14:15:12 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pixel_to_frame(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx.frame.addr + (y * data->mlx.frame.line_length + x
			* (data->mlx.frame.bpp / 8));
	*(unsigned int *)dst = color;
}
