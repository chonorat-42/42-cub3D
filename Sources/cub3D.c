/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:02:54 by chonorat          #+#    #+#             */
/*   Updated: 2023/11/24 12:44:31 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	valid_path(char *path)
{
	if (path && !ft_strncmp(path, "Maps/", 5))
		return (TRUE);
	return (FALSE);
}

static void	init_data(t_data *data)
{
	data->mlx.mlx = NULL;
	data->mlx.window = NULL;
	data->screen_res[0] = 0;
	data->screen_res[1] = 0;
	data->player.dir = 0;
	data->player.x_pos = 0;
	data->player.y_pos = 0;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 2 && valid_path(argv[1]))
	{
		init_data(&data);
		//PARSING
		parsing(argv[1], &argv[1][5]);
		// if (!start_mlx(&data))
		// 	return (free_data(&data), EXIT_FAILURE);
	}
	else
		return (print_error(ARGC, 0), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
