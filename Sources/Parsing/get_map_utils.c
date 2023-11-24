/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:12:13 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/24 13:27:59 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	delete_middle_node(t_dlst **temp)
{
	t_dlst	*next;
	t_dlst	*prev;

	prev = (*temp)->prev;
	next = (*temp)->next;
	prev->next = next;
	next->prev = prev;
	if ((*temp)->content)
		free((*temp)->content);
	free(*temp);
}

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
