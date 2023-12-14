/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:07:11 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/14 13:26:03 by pgouasmi         ###   ########.fr       */
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

void	parsing(t_data *data, char *file_path, char *file_name)
{
	int sprite;

	if (!is_extension_correct(file_name))
		return (exit(1));
	initialize_parser(&data->parser);
	get_file_content(&data->parser, file_path);
	init_data(data);
	get_trgb(data, &data->parser);
	if (open_textures(data, &data->parser))
		exit(1);
	map_parser(data, &data->parser);
	get_player_position(data);
	get_ennemy_position(data);
	if (data->ennemy.pres)
	{
		data->ghost.img = mlx_xpm_file_to_image(data->mlx.mlx, "Textures/ghost.xpm", &sprite, &sprite);
		if (!data->ghost.img)
			return (print_error(MALLOC, 0), free_data(data), exit(1));
	}
	get_exit_position(data);
	// free_parser(&data->parser);
}
