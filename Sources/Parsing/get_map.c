/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:57:34 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/22 19:48:06 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	add_to_maplst(t_maplst **lst, char *str)
{
	t_maplst	*new;
	t_maplst	*temp;
	char		*trim;

	new = malloc(sizeof(t_maplst));
	if (!new)
		return (1);
	trim = ft_strtrim(str, "\n");
	if (!trim)
		return (1);
	new->content = ft_strdup(trim);
	if (!new->content)
		return (free(new), free(trim), 1);
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (free(trim), 0);
}

size_t	maplst_size(t_maplst *lst)
{
	size_t		count;
	t_maplst	*temp;

	count = 0;
	temp = lst;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

void	lst_to_arr(t_parser *parser, t_maplst *lst)
{
	size_t		size;
	size_t		index;
	t_maplst	*temp;

	size = maplst_size(lst);
	parser->map = malloc(sizeof(char *) * size + 1);
	if (!parser->map)
		return (free_parser(parser), free_maplst(lst),
			print_error(MALLOC, 0), exit(1));
	index = 0;
	temp = lst;
	while (temp->next)
	{
		parser->map[index] = ft_strdup(temp->content);
		if (!parser->map[index])
			return (free_parser(parser), free_maplst(lst),
				print_error(MALLOC, 0), exit(1));
		index++;
		temp = temp->next;
	}
	parser->map[index] = NULL;
	free_maplst(lst);
}

void	get_map(t_parser *parser)
{
	t_maplst	*map_list;

	while (1)
	{
		parser->line = get_next_line(parser->fd);
		if (!parser->line)
			return (free_parser(parser), print_error(PARSING, NOMAP), exit(1));
		if (!str_isws(parser->line))
			break ;
		free(parser->line);
		parser->line = NULL;
	}
	map_list = NULL;
	if (add_to_maplst(&map_list, parser->line))
		return (free_parser(parser), free_maplst(map_list),
			print_error(MALLOC, 0), exit(1));
	free(parser->line);
	while (1)
	{
		parser->line = get_next_line(parser->fd);
		if (!parser->line)
			break ;
		if (add_to_maplst(&map_list, parser->line))
			return (free_parser(parser), free_maplst(map_list),
				print_error(MALLOC, 0), exit(1));
	}
	lst_to_arr(parser, map_list);
}
