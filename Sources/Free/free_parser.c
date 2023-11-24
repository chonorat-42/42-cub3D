/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:43:37 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/24 17:59:20 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	nullify_parser(t_parser *parser)
{
	parser->line = NULL;
	parser->textures.no_path = NULL;
	parser->textures.so_path = NULL;
	parser->textures.we_path = NULL;
	parser->textures.ea_path = NULL;
}

static void	free_textures(t_textures *textures)
{
	if (textures->no_path)
		free(textures->no_path);
	if (textures->so_path)
		free(textures->so_path);
	if (textures->we_path)
		free(textures->we_path);
	if (textures->ea_path)
		free(textures->ea_path);
}

void	free_parser(t_parser *parser)
{
	if (parser->line)
		free(parser->line);
	close(parser->fd);
	if (parser->map)
	{
		ft_free_arr(parser->map);
		parser->map = NULL;
	}
	free_textures(&parser->textures);
	nullify_parser(parser);
}
