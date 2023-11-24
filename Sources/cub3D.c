/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:02:54 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/24 18:14:48 by chonorat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	valid_path(char *path)
{
	if (path && !ft_strncmp(path, "Maps/", 5))
		return (TRUE);
	return (FALSE);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 2 && valid_path(argv[1]))
	{
		init_data(&data);
		//PARSING
		parsing(&data, argv[1], &argv[1][5]);
		if (!start_mlx(&data))
			return (free_data(&data), EXIT_FAILURE);
		free_data(&data);
	}
	else
		return (print_error(ARGC, 0), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
