/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:02:54 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/21 12:38:52 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	valid_path(char *path)
{
	if (path && !ft_strncmp(path, "Maps/", 5))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc == 2 && valid_path(argv[1]))
	{
		//PARSING
	}
	else
		return (print_error(ARGC, 0), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
