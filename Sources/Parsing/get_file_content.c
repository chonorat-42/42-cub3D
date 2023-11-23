/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:54:41 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/23 13:59:53 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	open_file(t_parser *parser, char *file_path)
{
	parser->fd = open(file_path, O_RDONLY);
	if (parser->fd == -1)
	{
		print_error(PARSING, OPEN);
		exit (1);
	}
}

void	get_file_content(t_parser *parser, char *file_path)
{
	open_file(parser, file_path);
	get_textures_and_colors(parser);
	get_map(parser);
}
