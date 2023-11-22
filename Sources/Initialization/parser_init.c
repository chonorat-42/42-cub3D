/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:17:26 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/22 17:56:48 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	initialize_colors(t_colors *colors)
{
	colors->c_flag = 0;
	colors->f_flag = 0;
}

static void	initialize_textures(t_textures *textures)
{
	textures->no_path = NULL;
	textures->no_flag = 0;
	textures->so_path = NULL;
	textures->so_flag = 0;
	textures->we_path = NULL;
	textures->we_flag = 0;
	textures->ea_path = NULL;
	textures->ea_flag = 0;
}

void	initialize_parser(t_parser *parser)
{
	parser->line = NULL;
	parser->map = NULL;
	initialize_textures(&parser->textures);
	initialize_colors(&parser->colors);
}
