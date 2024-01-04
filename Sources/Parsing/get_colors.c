/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:27:03 by pgouasmi          #+#    #+#             */
/*   Updated: 2024/01/04 14:46:37 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	parse_color(char *str, int nbr)
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

static int	check_color_end(t_parser *parser, char *str, int index)
{
	if (index < 2)
	{
		if (!ft_isdigit(str[0]))
			return (free_parser(parser), print_error(PARSING, COLORS), 1);
	}
	else
	{
		if (!ft_isstrws(str))
			return (free_parser(parser), print_error(PARSING, COLORS), 1);
	}
	return (0);
}

static int	get_each_color(t_parser *parser, int *color, size_t *i, int index)
{
	size_t	j;
	char	*current_color;

	j = *i;
	while (ft_isalnum(parser->line[*i]))
		(*i)++;
	if ((index < 2 && parser->line[*i] != ',') || (*i - j) > 3)
		return (free_parser(parser), print_error(PARSING, COLORS), 1);
	current_color = ft_substr(parser->line, j, *i - j);
	if (!current_color)
		return (free_parser(parser), print_error(MALLOC, 0), 1);
	color[index] = ft_atoi(current_color);
	if (parse_color(current_color, color[index]))
		return (free(current_color), free_parser(parser),
			print_error(PARSING, COLORS), 1);
	free(current_color);
	(*i)++;
	if (check_color_end(parser, &parser->line[*i], index))
		return (1);
	return (0);
}

void	get_colors(t_parser *parser, char *id, size_t *i)
{
	int		color[3];

	while (parser->line[*i] && ft_isws(parser->line[*i]))
		(*i)++;
	if (!ft_isalnum(parser->line[*i]))
		return (free_parser(parser), free(id),
			print_error(PARSING, COLORS), exit(1));
	if (get_each_color(parser, color, i, 0))
		return (free(id), exit(1));
	if (get_each_color(parser, color, i, 1))
		return (free(id), exit(1));
	if (get_each_color(parser, color, i, 2))
		return (free(id), exit(1));
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
