/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:05:18 by chonorat          #+#    #+#             */
/*   Updated: 2023/12/11 17:48:32 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	more_parsing_errors(int error)
{
	if (error == SPACEB)
	{
		ft_dprintf(2, "MAP : A white space ");
		return (ft_dprintf(2, "is not enclosed by `1'\n%s", END));
	}
	if (error == UNKCHAR)
		return (ft_dprintf(2, "MAP : Found an unknown character\n%s", END));
	if (error == EMPTYL)
		return (ft_dprintf(2, "MAP : Found an empty line\n%s", END));
	if (error == SEP)
		return (ft_dprintf(2, "MAP : The map is separated\n%s", END));
	if (error == DPX)
		return (ft_dprintf(2, "MAP : Several ennemies found\n%s", END));
	return (0);
}

static int	parsing_errors(int error)
{
	if (error == EXTENSION)
		return (ft_dprintf(2, "File's extension is not `.cub'\n%s", END));
	if (error == NOFNAME)
		return (ft_dprintf(2, "No file name before `.cub'\n%s", END));
	if (error == OPEN)
		return (ft_dprintf(2, "Could not open the map.\n%s", END));
	if (error == TEXTURES)
		return (ft_dprintf(2, "TEXTURES : Wrong syntax\n%s", END));
	if (error == TEXOP)
	{
		ft_dprintf(2, "TEXTURES : ");
		return (ft_dprintf(2, "A texture could not be opened\n%s", END));
	}
	if (error == COLORS)
		return (ft_dprintf(2, "COLORS : Wrong syntax\n%s", END));
	if (error == NOMAP)
		return (ft_dprintf(2, "MAP : No map found\n%s", END));
	if (error == NOP)
		return (ft_dprintf(2, "MAP : No player found\n%s", END));
	if (error == DPP)
		return (ft_dprintf(2, "MAP : Several players found\n%s", END));
	if (error == BORD)
		return (ft_dprintf(2, "MAP : Map is not enclosed by `1'\n%s", END));
	more_parsing_errors(error);
	return (0);
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
