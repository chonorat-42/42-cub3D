/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:33:36 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/08 22:08:56 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	apply_fog(int color, double fog_factor)
{
	int	red;
	int	green;
	int	blue;

	red = (color >> 16) & 0xFF;
	red = (int)(red * fog_factor);
	green = (color >> 8) & 0xFF;
	green = (int)(green * fog_factor);
	blue = color & 0xFF;
	blue = (int)(blue * fog_factor);
	return ((red << 16) | (green << 8) | blue);
}

int	get_fog(int color, double fog_intensity, double distance)
{
	double	fog_factor;
	int		final_color;

	fog_factor = 1.0 / (distance * fog_intensity);
	if (fog_factor > 0.5)
		fog_factor = 0.5;
	final_color = apply_fog(color, fog_factor);
	return (final_color);
}
