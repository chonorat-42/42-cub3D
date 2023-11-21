/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:05:18 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/21 19:25:50 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
void	parsing_errors(int error)
{
	if (error == EXTENSION)
		ft_dprintf(2, "File's extension is not `.cub'\n%s", END);
	if (error == NOFNAME)
		ft_dprintf(2, "No file name before `.cub'\n%s", END);
	if (error == OPEN)
		ft_dprintf(2, "Could not open the map. Do you have the right permissions?\n%s", END);
	if (error == TEXTURES)
		ft_dprintf(2, "Textures : Wrong syntax\n%s", END);
}

void	print_error(int type, int error)
{
	ft_dprintf(2, "%sError\n", RED);
	if (type == ARGC)
		ft_dprintf(2, "usage: ./cub3D Maps/map_name.cub\n%s", END);
	if (type == MALLOC)
		ft_dprintf(2, "Malloc error\n%s", END);
	if (type == PARSING)
		parsing_errors(error);
}
