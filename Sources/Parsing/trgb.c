/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trgb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:42:00 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/03 18:47:25 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	convert_trgb(int *colors, int transparency)
{
	return (transparency << 24 | colors[0] << 16 | colors[1] << 8 | colors[2]);
}

void	get_trgb(t_data *data, t_parser *parser)
{
	data->colors.ceiling = convert_trgb(parser->colors.c_colors, 0);
	data->colors.floor = convert_trgb(parser->colors.f_colors, 0);
}
