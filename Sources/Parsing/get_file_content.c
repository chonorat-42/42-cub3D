/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:54:41 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/22 19:47:20 by pgouasmi         ###   ########.fr       */
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

int	str_isws(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isws(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	get_texture_path(t_parser *parser, char *id, size_t	*i)
{
	size_t	j;

	while (ft_isws(parser->line[(*i)]))
		(*i)++;
	j = *i;
	while (!ft_isws(parser->line[*i]))
		(*i)++;
	if (!ft_strcmp(id, "NO"))
	{
		parser->textures.no_path = ft_substr(parser->line, j, *i);
		//printf("no_path = %s\n", parser->textures.no_path);
		if (!parser->textures.no_path)
			return (free(id), free_parser(parser), print_error(MALLOC, 0), exit(1));
	}
	if (!ft_strcmp(id, "SO"))
	{
		parser->textures.so_path = ft_substr(parser->line, j, *i);
		//printf("so_path = %s\n", parser->textures.so_path);
		if (!parser->textures.so_path)
			return (free(id), free_parser(parser), print_error(MALLOC, 0), exit(1));
	}
	if (!ft_strcmp(id, "WE"))
	{
		parser->textures.we_path = ft_substr(parser->line, j, *i);
		//printf("we_path = %s\n", parser->textures.we_path);
		if (!parser->textures.we_path)
			return (free(id), free_parser(parser), print_error(MALLOC, 0), exit(1));
	}
	if (!ft_strcmp(id, "EA"))
	{
		parser->textures.ea_path = ft_substr(parser->line, j, *i);
		//printf("ea_path = %s\n", parser->textures.ea_path);
		if (!parser->textures.ea_path)
			return (free(id), free_parser(parser), print_error(MALLOC, 0), exit(1));
	}
	if (!str_isws(&parser->line[*i]))
		return (free_parser(parser), print_error(PARSING, TEXTURES), exit(1));
}

int	parse_color(char *str, int nbr)
{
	size_t	i;

	if (nbr > 255 || nbr < 0)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	get_each_color(t_parser *parser, int *color, size_t *i, int index)
{
	size_t	j;
	char	*current_color;

	j = *i;
	while (ft_isalnum(parser->line[*i]))
		(*i)++;
	if (index < 2 && parser->line[*i] != ',')
		return (free_parser(parser), print_error(PARSING, COLORS), exit(1));
	current_color = ft_substr(parser->line, j, *i - j);
	if (!current_color)
		return (free_parser(parser), print_error(MALLOC, 0), exit(1));
	color[index] = ft_atoi(current_color);
	if (parse_color(current_color, color[index]))
		return (free(current_color), free_parser(parser),
			print_error(PARSING, COLORS), exit(1));
	free(current_color);
	(*i)++;
	if (index < 2)
	{
		if (!ft_isdigit(parser->line[*i]))
			return (free_parser(parser), print_error(PARSING, COLORS), exit(1));
	}
	else
	{
		if (!str_isws(&parser->line[*i]))
			return (free_parser(parser), print_error(PARSING, COLORS), exit(1));
	}
}

void	get_colors(t_parser *parser, char *id, size_t *i)
{
	int		color[3];

	while (parser->line[*i] && ft_isws(parser->line[*i]))
		(*i)++;
	if (!ft_isalnum(parser->line[*i]))
		return (free_parser(parser), print_error(PARSING, COLORS), exit(1));
	get_each_color(parser, color, i, 0);
	get_each_color(parser, color, i, 1);
	get_each_color(parser, color, i, 2);
	if (!ft_strcmp(id, "F"))
	{
		parser->colors.f_colors[0] = color[0];
		parser->colors.f_colors[1] = color[1];
		parser->colors.f_colors[2] = color[2];
		parser->colors.f_flag++;
		return ;
	}
	parser->colors.c_colors[0] = color[0];
	parser->colors.c_colors[1] = color[1];
	parser->colors.c_colors[2] = color[2];
	parser->colors.c_flag++;
}

void	parse_id(t_parser *parser, char *id, size_t	*i)
{
	if (!ft_strcmp(id, "NO"))
	{
		parser->textures.no_flag++;
		get_texture_path(parser, id, i);
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
		return (free_parser(parser), print_error(PARSING, TEXTURES), exit(1));
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
	if (!id)
		return (free_parser(parser), print_error(MALLOC, 0), exit(1));
	parse_id(parser, id, &i);
	free(id);
}

int	check_parsing_flags(t_textures textures, t_colors colors)
{
	if (textures.ea_flag != 1 || textures.no_flag != 1
		|| textures.so_flag != 1 || textures.we_flag != 1)
		return (0);
	if (colors.f_flag != 1 || colors.c_flag != 1)
		return (0);
	return (1);
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
		if (!str_isws(parser->line))
		{
			line_count++;
			parse_line(parser, parser->line);
			free(parser->line);
			parser->line = NULL;
			if (line_count == 6)
			{
				if (!check_parsing_flags(parser->textures, parser->colors))
					return (print_error(PARSING, TEXTURES),
						free_parser(parser), exit(1));
				break ;
			}
		}
	}
}

void	get_file_content(t_parser *parser, char *file_path)
{
	open_file(parser, file_path);
	get_textures(parser);
	get_map(parser);
}
