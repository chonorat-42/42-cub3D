/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:07:11 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/15 16:08:39 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_extension_correct(char *str)
{
	size_t	i;

	i = ft_strlen(str);
	while (i && str[i] != '.')
		i--;
	if (!i)
	{
		print_error(PARSING, NOFNAME);
		return (0);
	}
	if (ft_strcmp(&str[i], ".cub"))
	{
		print_error(PARSING, EXTENSION);
		return (0);
	}
	return (1);
}

static void	save_data(t_data *data)
{
	data->saved_data.x_pos = data->player.x_pos;
	data->saved_data.y_pos = data->player.y_pos;
	data->saved_data.angle = data->player.angle;
	if (data->ennemy.pres)
	{
		data->saved_data.ennemy_pos[0] = data->ennemy.pos[0];
		data->saved_data.ennemy_pos[1] = data->ennemy.pos[1];
	}
}

void	parsing(t_data *data, char *file_path, char *file_name)
{
	if (!is_extension_correct(file_name))
		return (exit(1));
	initialize_parser(&data->parser);
	init_data(data);
	get_file_content(&data->parser, file_path);
	get_trgb(data, &data->parser);
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (free_data(data), print_error(MALLOC, 0), exit(1));
	open_textures(data, &data->parser);
	map_parser(data, &data->parser);
	get_player_position(data);
	get_ennemy_position(data);
	get_exit_position(data);
	save_data(data);
}
