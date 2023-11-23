/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:57:34 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/23 17:48:12 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	initialize_dlst_content(t_dlst *new, char *str)
{
	char	*trim;

	trim = ft_strtrim(str, "\n");
	if (!trim)
		return (1);
	new->content = ft_strdup(trim);
	if (!new->content)
		return (free(new), free(trim), 1);
	free(trim);
	return (0);
}

int	add_to_maplst(t_dlst **lst, char *str)
{
	t_dlst		*new;
	t_dlst		*temp;

	new = malloc(sizeof(t_dlst));
	if (!new)
		return (1);
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	if (initialize_dlst_content(new, str))
		return (free(new), 1);
	return (0);
}

size_t	maplst_size(t_dlst *lst)
{
	size_t	count;
	t_dlst	*temp;

	count = 1;
	temp = lst;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

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
		{
			prev = temp->prev;
			next = temp->next;
			prev->next = next;
			next->prev = prev;
			if (temp->content)
				free(temp->content);
			free(temp);

		}
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
			temp = temp->next;
			temp->prev = NULL;
			prev = temp->prev;
			*lst = temp;
			if (prev->content)
				free(prev->content);
			free(prev);
		}
		else
		{
			prev = temp->prev;
			next = temp->next;
			prev->next = next;
			next->prev = prev;
			if (temp->content)
				free(temp->content);
			free(temp);
		}
		temp = temp->next;
	}
}

void	print_arr(char **arr)
{
	size_t i = 0;

	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void print_dlst(t_dlst *lst)
{
	t_dlst *temp;

	temp = lst;
	printf("in printdlist\n");
	while (temp)
	{
		printf("%s\n", temp->content);
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
	}
	// print_dlst(map_list);
	remove_empty_up(&map_list);
	// printf("\n");
	// print_dlst(map_list);
	remove_empty_down(&map_list);
	// printf("\n");
	// print_dlst(map_list);
	lst_to_arr(parser, map_list);
	// printf("\n");
	print_arr(parser->map);
}
