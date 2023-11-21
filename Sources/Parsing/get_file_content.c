/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:54:41 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/21 19:33:34 by pgouasmi         ###   ########.fr       */
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

int remaining_char(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isws(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	get_texture_path(t_parser *parser, char *id, size_t	*i, char *type)
{
	size_t	j;

	while (ft_isws(parser->line[(*i)]))
		(*i)++;
	j = *i;
	while (!ft_isws(parser->line[*i]))
		(*i)++;
	if (!ft_strcmp(type, "NO"))
	{
		parser->textures.no_path = ft_substr(parser->line, j, *i);
		printf("no_path = %s\n", parser->textures.no_path);
		if (!parser->textures.no_path)
			return (free(id), free_parser(parser), print_error(MALLOC, 0) ,exit(1));
	}
	if (!ft_strcmp(type, "SO"))
	{
		parser->textures.so_path = ft_substr(parser->line, j, *i);
		printf("so_path = %s\n", parser->textures.no_path);
		if (!parser->textures.so_path)
			return (free(id), free_parser(parser), print_error(MALLOC, 0) ,exit(1));
	}
	if (!ft_strcmp(type, "WE"))
	{
		parser->textures.we_path = ft_substr(parser->line, j, *i);
		printf("we_path = %s\n", parser->textures.no_path);
		if (!parser->textures.we_path)
			return (free(id), free_parser(parser), print_error(MALLOC, 0) ,exit(1));
	}
	if (!ft_strcmp(type, "EA"))
	{
		parser->textures.ea_path = ft_substr(parser->line, j, *i);
		printf("ea_path = %s\n", parser->textures.no_path);
		if (!parser->textures.ea_path)
			return (free(id), free_parser(parser), print_error(MALLOC, 0) ,exit(1));
	}
	if (remaining_char(&parser->line[*i]))
		return (free_parser(parser), print_error(PARSING, TEXTURES), exit(1));
}

void	parse_id(t_parser *parser, char *id, size_t	*i)
{
	if (!ft_strcmp(id, "NO"))
	{
		parser->textures.no_flag = 1;
		get_texture_path(parser, id, i, "NO");
	}
	if (!ft_strcmp(id, "SO"))
	{
		parser->textures.so_flag = 1;
		get_texture_path(parser, id, i, "SO");
	}
	if (!ft_strcmp(id, "WE"))
	{
		parser->textures.we_flag = 1;
		get_texture_path(parser, id, i, "WE");
	}
	if (!ft_strcmp(id, "EA"))
	{
		parser->textures.ea_flag = 1;
		get_texture_path(parser, id, i, "EA");
	}
}

void	parse_line(t_parser *parser, char *line)
{
	size_t	i;
	size_t	j;
	char	*id;

	i = 0;
	while (line[i] && ft_isws(line[i]))
		i++;
	j = i;
	while (line[i] && !ft_isws(line[i]))
		i++;
	id = ft_substr(line, j, i);
	printf("id = %s\n", id);
	if (!id)
		return (free_parser(parser), print_error(MALLOC, 0), exit(1));
	parse_id(parser, id, &i);
	free(id);
}

void	get_textures(t_parser *parser)
{
	while (1)
	{
		parser->line = get_next_line(parser->fd);
		if (!parser->line)
			break ;
		if (parser->line[0] != '\n')
		{
			printf("line = %s\n", parser->line);
			parse_line(parser, parser->line);
			free(parser->line);
		}
	}
}

void	get_file_content(t_parser *parser, char *file_path)
{
	open_file(parser, file_path);
	get_textures(parser);
}
