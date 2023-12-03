/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:09:02 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/12/03 18:49:34 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_east_and_west(t_parser *parser, char *id, size_t *i, size_t j)
{
	if (!ft_strcmp(id, "WE"))
	{
		parser->textures.we_path = ft_substr(parser->line, j, *i - j);
		if (!parser->textures.we_path)
			return (free(id), free_parser(parser),
				print_error(MALLOC, 0), exit(1));
	}
	if (!ft_strcmp(id, "EA"))
	{
		parser->textures.ea_path = ft_substr(parser->line, j, *i - j);
		if (!parser->textures.ea_path)
			return (free(id), free_parser(parser),
				print_error(MALLOC, 0), exit(1));
	}
}

void	get_north_and_south(t_parser *parser, char *id, size_t *i, size_t j)
{
	if (!ft_strcmp(id, "NO"))
	{
		parser->textures.no_path = ft_substr(parser->line, j, (*i - j));
		if (!parser->textures.no_path)
			return (free(id), free_parser(parser),
				print_error(MALLOC, 0), exit(1));
	}
	if (!ft_strcmp(id, "SO"))
	{
		parser->textures.so_path = ft_substr(parser->line, j, (*i - j));
		if (!parser->textures.so_path)
			return (free(id), free_parser(parser),
				print_error(MALLOC, 0), exit(1));
	}
}

void	get_texture_path(t_parser *parser, char *id, size_t	*i)
{
	size_t	j;

	while (parser->line[*i] && ft_isws(parser->line[(*i)]))
		(*i)++;
	j = *i;
	while (parser->line[*i] && !ft_isws(parser->line[*i]))
		(*i)++;
	if (!ft_isstrws(&parser->line[*i]))
		return (free_parser(parser),
			print_error(PARSING, TEXTURES), exit(1));
	get_north_and_south(parser, id, i, j);
	get_east_and_west(parser, id, i, j);
}

void	parse_id(t_parser *parser, char *id, size_t *i)
{
	if (!ft_strcmp(id, "NO"))
	{
		parser->textures.no_flag++;
		get_texture_path (parser, id, i);
	}
	else if (!ft_strcmp(id, "SO"))
	{
		parser->textures.so_flag++;
		get_texture_path(parser, id, i);
	}
	else if (!ft_strcmp(id, "WE"))
	{
		parser->textures.we_flag++;
		get_texture_path(parser, id, i);
	}
	else if (!ft_strcmp(id, "EA"))
	{
		parser->textures.ea_flag++;
		get_texture_path(parser, id, i);
	}
	else if (!ft_strcmp(id, "F") || !ft_strcmp(id, "C"))
		get_colors(parser, id, i);
	else
		return (free_parser(parser), free(id),
			print_error(PARSING, TEXTURES), exit(1));
}

void	get_textures(t_parser *parser)
{
	size_t	line_count;

	line_count = 0;
	while (1)
	{
		parser->line = get_next_line(parser->fd);
		if (!parser->line)
			break ;
		if (!ft_isstrws(parser->line))
		{
			line_found(parser, &line_count);
			if (line_count == 6)
			{
				if (!check_parsing_flags(parser->textures, parser->colors))
					return (print_error(PARSING, TEXTURES),
						free_parser(parser), exit(1));
				break ;
			}
		}
		free(parser->line);
		parser->line = NULL;
	}
}
