/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:57:34 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/24 13:27:08 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	lst_to_arr(t_parser *parser, t_dlst *lst)
{
	size_t	size;
	size_t	index;
	t_dlst	*temp;

	size = maplst_size(lst);
	parser->map = malloc(sizeof(char *) * size + 1);
	if (!parser->map)
		return (free_parser(parser), free_maplst(lst),
			print_error(MALLOC, 0), exit(1));
	index = 0;
	temp = lst;
	while (temp)
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

void	parse_before_map(t_parser *parser, t_dlst **lst)
{
	while (1)
	{
		parser->line = get_next_line(parser->fd);
		if (!parser->line)
			return (free_parser(parser), print_error(PARSING, NOMAP), exit(1));
		if (!ft_isstrws(parser->line))
			break ;
		free(parser->line);
		parser->line = NULL;
	}
	if (add_to_maplst(lst, parser->line))
		return (free_parser(parser), free_maplst(*lst),
			print_error(MALLOC, 0), exit(1));
	free(parser->line);
}

void	remove_empty_down(t_dlst **lst)
{
	t_dlst	*temp;
	t_dlst	*prev;
	t_dlst	*next;

	temp = *lst;
	while (temp->next)
		temp = temp->next;
	while (!temp->content[0] || ft_isstrws(temp->content))
	{
		if (temp->next == NULL)
		{
			prev = temp->prev;
			next = NULL;
			prev->next = next;
			if (temp->content)
				free(temp->content);
			free(temp);
			temp = prev;
		}
		else
			delete_middle_node(&temp);
	}
}

void	remove_empty_up(t_dlst **lst)
{
	t_dlst	*temp;
	t_dlst	*prev;
	t_dlst	*next;

	temp = *lst;
	while (!temp->content[0] || ft_isstrws(temp->content))
	{
		if (temp == *lst)
		{
			prev = NULL;
			next = temp->next;
			prev->next = next;
			if (temp->content)
				free(temp->content);
			free(temp);
			temp = prev;
		}
		else
			delete_middle_node(&temp);
		temp = temp->next;
	}
}

void	get_map(t_parser *parser)
{
	t_dlst	*map_list;

	map_list = NULL;
	parse_before_map(parser, &map_list);
	while (1)
	{
		parser->line = get_next_line(parser->fd);
		if (!parser->line)
			break ;
		if (add_to_maplst(&map_list, parser->line))
			return (free_parser(parser), free_maplst(map_list),
				print_error(MALLOC, 0), exit(1));
		if (parser->line)
		{
			free(parser->line);
			parser->line = NULL;
		}
	}
	remove_empty_up(&map_list);
	remove_empty_down(&map_list);
	lst_to_arr(parser, map_list);
	print_arr(parser->map);
}
