/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:07:54 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/24 13:35:12 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	printf("\n");
}

void	print_dlst(t_dlst *lst)
{
	t_dlst	*temp;

	temp = lst;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	printf("\n");
}
